#include "kernel.hh"
#include "k-vmiter.hh"

// k-memviewer.cc
//
//    The `memusage` class tracks memory usage by walking page tables,
//    looks for errors, and prints the memory map to the console.


class memusage {
  public:
    // tracks physical addresses in the range [0, maxpa)
    static constexpr uintptr_t maxpa = 1024 * PAGESIZE;
    // shows physical addresses in the range [0, max_view_pa)
    static constexpr uintptr_t max_view_pa = 512 * PAGESIZE;
    // shows virtual addresses in the range [0, max_view_va)
    static constexpr uintptr_t max_view_va = 768 * PAGESIZE;

    memusage()
        : v_(nullptr) {
    }

    // Flag bits for memory types:
    static constexpr unsigned f_kernel = 1;     // kernel-restricted
    static constexpr unsigned f_user = 2;       // user-accessible
    // `f_process(pid)` is for memory associated with process `pid`
    static constexpr unsigned f_process(int pid) {
        if (pid >= 30) {
            return 2U << 31;
        } else if (pid >= 1) {
            return 2U << pid;
        } else {
            return 0;
        }
    }
    // Pages such as process page tables and `struct proc` are counted
    // both as kernel-only and process-associated.


    // Refresh the memory map from current state
    void refresh();

    // Return the symbol (character & color) associated with `pa`
    uint16_t symbol_at(uintptr_t pa) const;

  private:
    unsigned* v_;

    // add `flags` to the page containing `pa`
    // This is safe to call even if `pa >= maxpa`.
    void mark(uintptr_t pa, unsigned flags) {
        if (pa < maxpa) {
            v_[pa / PAGESIZE] |= flags;
        }
    }
    // return one of the processes set in a mark
    static int marked_pid(unsigned v) {
        return lsb(v >> 2);
    }
    // print an error about a page table
    void page_error(uintptr_t pa, const char* desc, int pid) const;
};


// memusage::refresh()
//    Calculate the current physical usage map, using the current process
//    table.

void memusage::refresh() {
    if (!v_) {
        v_ = reinterpret_cast<unsigned*>(kalloc(PAGESIZE));
        assert(v_ != nullptr);
    }

    memset(v_, 0, (maxpa / PAGESIZE) * sizeof(*v_));

    // mark kernel page tables
    for (ptiter it(kernel_pagetable); !it.done(); it.next()) {
        mark(it.pa(), f_kernel);
    }
    mark(kptr2pa(kernel_pagetable), f_kernel);

    // mark pages accessible from each process's page table
    bool any = false;
    for (int pid = 1; pid < NPROC; ++pid) {
        proc* p = &ptable[pid];
        if (p->state != P_FREE
            && p->pagetable
            && p->pagetable != kernel_pagetable) {
            any = true;

            for (ptiter it(p); it.va() < VA_LOWEND; it.next()) {
                mark(it.pa(), f_kernel | f_process(pid));
            }
            mark(kptr2pa(p->pagetable), f_kernel | f_process(pid));

            for (vmiter it(p, 0); it.va() < VA_LOWEND; ) {
                if (it.user()) {
                    mark(it.pa(), f_user | f_process(pid));
                    it.next();
                } else {
                    it.next_range();
                }
            }
        }
    }

    // if no different process page tables, use physical address instead
    if (!any) {
        for (vmiter it(kernel_pagetable, 0); it.va() < VA_LOWEND; ) {
            if (it.user()
                && it.pa() < MEMSIZE_PHYSICAL
                && physpages[it.pa() / PAGESIZE].used()) {
                unsigned owner = (it.pa() - PROC_START_ADDR) / 0x40000;
                mark(it.pa(), f_user | f_process(owner + 1));
                it.next();
            } else {
                it.next_range();
            }
        }
    }

    // mark my own memory
    if (any) {
        mark(kptr2pa(v_), f_kernel);
    }
}

void memusage::page_error(uintptr_t pa, const char* desc, int pid) const {
    const char* fmt = pid >= 0
        ? "PAGE TABLE ERROR: %lx: %s (pid %d)\n"
        : "PAGE TABLE ERROR: %lx: %s\n";
    error_printf(CPOS(22, 0), COLOR_ERROR, fmt, pa, desc, pid);
    log_printf(fmt, pa, desc, pid);
}

uint16_t memusage::symbol_at(uintptr_t pa) const {
    bool is_reserved = reserved_physical_address(pa);
    bool is_kernel = !is_reserved && !allocatable_physical_address(pa);

    if (pa >= maxpa) {
        if (is_kernel) {
            return 'K' | 0x4000;
        } else if (is_reserved) {
            return '?' | 0x4000;
        } else {
            return '?' | 0xF000;
        }
    }

    auto v = v_[pa / PAGESIZE];
    if (pa >= (uintptr_t) console && pa < (uintptr_t) console + PAGESIZE) {
        return 'C' | 0x0700;
    } else if (is_reserved && v > (f_kernel | f_user)) {
        page_error(pa, "reserved page mapped for user", marked_pid(v));
        return 'R' | 0x0C00;
    } else if (is_reserved) {
        return 'R' | 0x0700;
    } else if (is_kernel && v > (f_kernel | f_user)) {
        page_error(pa, "kernel data page mapped for user", marked_pid(v));
        return 'K' | 0xCD00;
    } else if (is_kernel) {
        return 'K' | 0x0D00;
    } else if (pa >= MEMSIZE_PHYSICAL) {
        return ' ' | 0x0700;
    } else {
        if (v == 0) {
            if (physpages[pa / PAGESIZE].used()) {
                // Leaked page: used but not referenced by anything we know
                return 'L' | 0x0300;
            } else {
                return '.' | 0x0700;
            }
        } else if (v == f_kernel) {
            return 'K' | 0x0D00;
        } else if (v == f_user) {
            return '.' | 0x0700;
        } else if ((v & f_kernel) && (v & f_user)) {
            page_error(pa, "kernel allocated page mapped for user",
                       marked_pid(v));
            return '*' | 0xF400;
        } else {
            // find lowest process involved with this page
            pid_t pid = marked_pid(v);
            // foreground color is that associated with `pid`
            static const uint8_t colors[] = { 0xF, 0xC, 0xA, 0x9, 0xE };
            uint16_t ch = colors[pid % 5] << 8;
            if (v & f_kernel) {
                // kernel page: dark red background
                ch = 0x4000 | (ch == 0x0C00 ? 0x0F00 : ch);
            }
            if (!physpages[pa / PAGESIZE].used()) {
                // Dangling reference: referenced but marked as free
                page_error(pa, "freed page mapped for user", pid);
                ch |= 0xF000;
            }
            if (v > (f_process(pid) | f_kernel | f_user)) {
                // shared page
                ch = 0x0F00 | 'S';
            } else {
                // non-shared page
                static const char names[] = "K123456789ABCDEFGHIJKLMNOPQRST??";
                ch |= names[pid];
            }
            return ch;
        }
    }
}


static void console_memviewer_virtual(memusage& mu, proc* vmp) {
    assert(vmp->pagetable != nullptr);

    const char* statemsg = vmp->state == P_FAULTED ? " (faulted)" : "";
    console_printf(CPOS(10, 26), 0x0F00,
                   "VIRTUAL ADDRESS SPACE FOR %d%C%s\n", vmp->pid,
                   0x0700, statemsg);

    for (vmiter it(vmp, 0);
         it.va() < memusage::max_view_va;
         it += PAGESIZE) {
        unsigned long pn = it.va() / PAGESIZE;
        if (pn % 64 == 0) {
            console_printf(CPOS(11 + pn / 64, 3), 0x0F00,
                           "0x%06X ", it.va());
        }
        uint16_t ch;
        if (!it.present()) {
            ch = ' ';
        } else {
            ch = mu.symbol_at(it.pa());
            if (it.user()) { // switch foreground & background colors
                if (ch == (0x0F00 | 'S')) {
                    ch ^= 0xFE00;
                } else {
                    uint16_t z = (ch & 0x0F00) ^ ((ch & 0xF000) >> 4);
                    ch ^= z | (z << 4);
                }
            }
        }
        console[CPOS(11 + pn/64, 12 + pn%64)] = ch;
    }
}


void console_memviewer(proc* vmp) {
    // Process 0 must never be used.
    assert(ptable[0].state == P_FREE);

    // track physical memory
    static memusage mu;
    mu.refresh();

    // print physical memory
    console_printf(CPOS(0, 32), 0x0F00, "PHYSICAL MEMORY\n");

    for (int pn = 0; pn * PAGESIZE < memusage::max_view_pa; ++pn) {
        if (pn % 64 == 0) {
            console_printf(CPOS(1 + pn/64, 3), 0x0F00, "0x%06X ", pn << 12);
        }
        console[CPOS(1 + pn/64, 12 + pn%64)] = mu.symbol_at(pn * PAGESIZE);
    }

    // print virtual memory
    if (vmp) {
        console_memviewer_virtual(mu, vmp);
    }
}
