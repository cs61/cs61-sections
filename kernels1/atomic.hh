#ifndef WEENSYOS_ATOMIC_HH
#define WEENSYOS_ATOMIC_HH

enum class memory_order : int {
	relaxed, consume, acquire, release, acq_rel, seq_cst
};

inline constexpr memory_order memory_order_relaxed = memory_order::relaxed;
inline constexpr memory_order memory_order_consume = memory_order::consume;
inline constexpr memory_order memory_order_acquire = memory_order::acquire;
inline constexpr memory_order memory_order_release = memory_order::release;
inline constexpr memory_order memory_order_acq_rel = memory_order::acq_rel;
inline constexpr memory_order memory_order_seq_cst = memory_order::seq_cst;

constexpr memory_order __cmpexch_failure_order(memory_order m) noexcept {
	return m == memory_order::acq_rel ? memory_order::acquire : m == memory_order::release ? memory_order::relaxed : m;
}

template <typename T> struct atomic;

template <typename T> struct __atomic_base {
	using value_type = T;
	using difference_type = value_type;
	static constexpr int _alignment = sizeof(T) > alignof(T) ? sizeof(T) : alignof(T);

private:
	alignas(_alignment) T _value = 0;

public:
	__atomic_base() noexcept = default;
	~__atomic_base() noexcept = default;
	__atomic_base(const __atomic_base&) = delete;
	__atomic_base& operator=(const __atomic_base&) = delete;
	__atomic_base& operator=(const __atomic_base&) volatile = delete;

	constexpr __atomic_base(T i) noexcept : _value(i)	{ }

	operator T() const noexcept							{ return load(); }
	operator T() const volatile noexcept				{ return load(); }
	T operator=(T i) noexcept							{ store(i); return i; }
	T operator=(T i) volatile noexcept					{ store(i); return i; }
	T operator++(int) noexcept							{ return fetch_add(1); }
	T operator++(int) volatile noexcept					{ return fetch_add(1); }
	T operator--(int) noexcept							{ return fetch_sub(1); }
	T operator--(int) volatile noexcept					{ return fetch_sub(1); }
	T operator++() noexcept								{ return __atomic_add_fetch(&_value, 1, int(memory_order::seq_cst)); }
	T operator++() volatile noexcept					{ return __atomic_add_fetch(&_value, 1, int(memory_order::seq_cst)); }
	T operator--() noexcept								{ return __atomic_sub_fetch(&_value, 1, int(memory_order::seq_cst)); }
	T operator--() volatile noexcept					{ return __atomic_sub_fetch(&_value, 1, int(memory_order::seq_cst)); }
	T operator+=(T i) noexcept							{ return __atomic_add_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator+=(T i) volatile noexcept					{ return __atomic_add_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator-=(T i) noexcept							{ return __atomic_sub_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator-=(T i) volatile noexcept					{ return __atomic_sub_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator&=(T i) noexcept							{ return __atomic_and_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator&=(T i) volatile noexcept					{ return __atomic_and_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator|=(T i) noexcept							{ return __atomic_or_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator|=(T i) volatile noexcept					{ return __atomic_or_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator^=(T i) noexcept							{ return __atomic_xor_fetch(&_value, i, int(memory_order::seq_cst)); }
	T operator^=(T i) volatile noexcept					{ return __atomic_xor_fetch(&_value, i, int(memory_order::seq_cst)); }

	bool is_lock_free() const noexcept					{ return __atomic_is_lock_free(sizeof(T), reinterpret_cast<void*>(-_alignment)); }
	bool is_lock_free() const volatile noexcept			{ return __atomic_is_lock_free(sizeof(T), reinterpret_cast<void*>(-_alignment)); }

	__always_inline T load(memory_order m = memory_order::seq_cst) const noexcept { return __atomic_load_n(&_value, int(m)); }
	__always_inline T load(memory_order m = memory_order::seq_cst) const volatile noexcept { return __atomic_load_n(&_value, int(m)); }
	__always_inline void store(T i, memory_order m = memory_order::seq_cst) noexcept { __atomic_store_n(&_value, i, int(m)); }
	__always_inline void store(T i, memory_order m = memory_order::seq_cst) volatile noexcept { __atomic_store_n(&_value, i, int(m)); }

	__always_inline T exchange(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_exchange_n(&_value, i, int(m)); }
	__always_inline T exchange(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_exchange_n(&_value, i, int(m)); }

	__always_inline bool compare_exchange_weak(T& expected, T desired, memory_order success_order, memory_order failure_order) noexcept {
		return __atomic_compare_exchange_n(&_value, &expected, desired, 1, int(success_order), int(failure_order));
	}
	__always_inline bool compare_exchange_weak(T& expected, T desired, memory_order success_order, memory_order failure_order) volatile noexcept {
		return __atomic_compare_exchange_n(&_value, &expected, desired, 1, int(success_order), int(failure_order));
	}
	__always_inline bool compare_exchange_weak(T& expected, T desired, memory_order m = memory_order::seq_cst) noexcept {
		return compare_exchange_weak(expected, desired, m, __cmpexch_failure_order(m));
	}
	__always_inline bool compare_exchange_weak(T& expected, T desired, memory_order m = memory_order::seq_cst) volatile noexcept {
		return compare_exchange_weak(expected, desired, m, __cmpexch_failure_order(m));
	}

	__always_inline bool compare_exchange_strong(T& expected, T desired, memory_order success_order, memory_order failure_order) noexcept {
		return __atomic_compare_exchange_n(&_value, &expected, desired, 0, int(success_order), int(failure_order));
	}
	__always_inline bool compare_exchange_strong(T& expected, T desired, memory_order success_order, memory_order failure_order) volatile noexcept {
		return __atomic_compare_exchange_n(&_value, &expected, desired, 0, int(success_order), int(failure_order));
	}
	__always_inline bool compare_exchange_strong(T& expected, T desired, memory_order m = memory_order::seq_cst) noexcept {
		return compare_exchange_strong(expected, desired, m, __cmpexch_failure_order(m));
	}
	__always_inline bool compare_exchange_strong(T& expected, T desired, memory_order m = memory_order::seq_cst) volatile noexcept {
		return compare_exchange_strong(expected, desired, m, __cmpexch_failure_order(m));
	}

	__always_inline T fetch_add(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_fetch_add(&_value, i, int(m)); }
	__always_inline T fetch_add(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_fetch_add(&_value, i, int(m)); }
	__always_inline T fetch_sub(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_fetch_sub(&_value, i, int(m)); }
	__always_inline T fetch_sub(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_fetch_sub(&_value, i, int(m)); }
	__always_inline T fetch_and(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_fetch_and(&_value, i, int(m)); }
	__always_inline T fetch_and(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_fetch_and(&_value, i, int(m)); }
	__always_inline T fetch_or(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_fetch_or(&_value, i, int(m)); }
	__always_inline T fetch_or(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_fetch_or(&_value, i, int(m)); }
	__always_inline T fetch_xor(T i, memory_order m = memory_order::seq_cst) noexcept { return __atomic_fetch_xor(&_value, i, int(m)); }
	__always_inline T fetch_xor(T i, memory_order m = memory_order::seq_cst) volatile noexcept { return __atomic_fetch_xor(&_value, i, int(m)); }
};

template <typename T> struct atomic {
	atomic() = delete;
	~atomic() = delete;
};

template <> struct atomic<bool> {
	using value_type = bool;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(value_type), reinterpret_cast<void*>(-1));

private:
	__atomic_base<bool> _base;

public:
	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;

	constexpr atomic(bool i) noexcept : _base(i)		{ }

	operator bool() const noexcept						{ return _base.load(); }
	operator bool() const volatile noexcept				{ return _base.load(); }
	bool operator=(bool i) noexcept						{ return _base.operator=(i); }
	bool operator=(bool i) volatile noexcept			{ return _base.operator=(i); }

	bool is_lock_free() const noexcept					{ return _base.is_lock_free(); }
	bool is_lock_free() const volatile noexcept			{ return _base.is_lock_free(); }

	bool load(memory_order m = memory_order::seq_cst) const noexcept { return _base.load(m); }
	bool load(memory_order m = memory_order::seq_cst) const volatile noexcept { return _base.load(m); }
	void store(bool i, memory_order m = memory_order::seq_cst) noexcept { _base.store(i, m); }
	void store(bool i, memory_order m = memory_order::seq_cst) volatile noexcept { _base.store(i, m); }

	bool exchange(bool i, memory_order m = memory_order::seq_cst) noexcept { return _base.exchange(i, m); }
	bool exchange(bool i, memory_order m = memory_order::seq_cst) volatile noexcept { return _base.exchange(i, m); }

	bool compare_exchange_weak(bool& expected, bool desired, memory_order success_order, memory_order failure_order) noexcept {
		return _base.compare_exchange_weak(expected, desired, success_order, failure_order);
	}
	bool compare_exchange_weak(bool& expected, bool desired, memory_order success_order, memory_order failure_order) volatile noexcept {
		return _base.compare_exchange_weak(expected, desired, success_order, failure_order);
	}
	bool compare_exchange_weak(bool& expected, bool desired, memory_order m = memory_order::seq_cst) noexcept {
		return _base.compare_exchange_weak(expected, desired, m);
	}
	bool compare_exchange_weak(bool& expected, bool desired, memory_order m = memory_order::seq_cst) volatile noexcept {
		return _base.compare_exchange_weak(expected, desired, m);
	}

	bool compare_exchange_strong(bool& expected, bool desired, memory_order success_order, memory_order failure_order) noexcept {
		return _base.compare_exchange_strong(expected, desired, success_order, failure_order);
	}
	bool compare_exchange_strong(bool& expected, bool desired, memory_order success_order, memory_order failure_order) volatile noexcept {
		return _base.compare_exchange_strong(expected, desired, success_order, failure_order);
	}
	bool compare_exchange_strong(bool& expected, bool desired, memory_order m = memory_order::seq_cst) noexcept {
		return _base.compare_exchange_strong(expected, desired, m);
	}
	bool compare_exchange_strong(bool& expected, bool desired, memory_order m = memory_order::seq_cst) volatile noexcept {
		return _base.compare_exchange_strong(expected, desired, m);
	}
};

template <> struct atomic<char> : __atomic_base<char> {
	using __integral_type = char;
	using __base_type = __atomic_base<char>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<signed char> : __atomic_base<signed char> {
	using __integral_type = signed char;
	using __base_type = __atomic_base<signed char>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<unsigned char> : __atomic_base<unsigned char> {
	using __integral_type = unsigned char;
	using __base_type = __atomic_base<unsigned char>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<short> : __atomic_base<short> {
	using __integral_type = short;
	using __base_type = __atomic_base<short>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<unsigned short> : __atomic_base<unsigned short> {
	using __integral_type = unsigned short;
	using __base_type = __atomic_base<unsigned short>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<int> : __atomic_base<int> {
	using __integral_type = int;
	using __base_type = __atomic_base<int>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<unsigned> : __atomic_base<unsigned> {
	using __integral_type = unsigned;
	using __base_type = __atomic_base<unsigned>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<long> : __atomic_base<long> {
	using __integral_type = long;
	using __base_type = __atomic_base<long>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<unsigned long> : __atomic_base<unsigned long> {
	using __integral_type = unsigned long;
	using __base_type = __atomic_base<unsigned long>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<long long> : __atomic_base<long long> {
	using __integral_type = long long;
	using __base_type = __atomic_base<long long>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

template <> struct atomic<unsigned long long> : __atomic_base<unsigned long long> {
	using __integral_type = unsigned long long;
	using __base_type = __atomic_base<unsigned long long>;
	static constexpr bool is_always_lock_free = __atomic_always_lock_free(sizeof(__integral_type), reinterpret_cast<void*>(-__base_type::_alignment));

	atomic() noexcept = default;
	~atomic() noexcept = default;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;
	constexpr atomic(__integral_type i) noexcept : __base_type(i) { }
	using __base_type::operator __integral_type;
	using __base_type::operator=;
};

#endif
