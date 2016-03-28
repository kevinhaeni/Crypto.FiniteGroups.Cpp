#pragma once

namespace MathUtils{

	template <typename T>
	inline static T modpow(T base, T exp, T modulus) {
		base %= modulus;
		T result = 1;
		while (exp > 0) {
			if (exp & 1) result = (result * base) % modulus;
			base = (base * base) % modulus;
			exp >>= 1;
		}
		return result;

	}

	static inline int gcd(int a, int b)
	{
		while (b != 0)
		{
			int c = a % b;
			a = b;
			b = c;
		}
		return a;
	}

	static inline int phi(int n)
	{
		int x = 0;
		for (int i = 1; i <= n; i++)
		{
			if (gcd(n, i) == 1)
				x++;
		}
		return x;
	}

	static inline bool IsPrime(int number)
	{
		int i;

		for (i = 2; i<number; i++)
		{
			if (number % i == 0)
			{
				return false;
			}
		}

		return true;
	}


}