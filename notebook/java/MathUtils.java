package modules;

import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Created by triveni on 14/7/17.
 */
public class MathUtils {
	private static String PI = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819";
	public static long powMod(long a, long b, long m) {
		long ans = 1;
		while (b > 0) {
			if (b % 2 == 1) ans = ans * a % m;
			b >>= 1;
			a = a * a % m;
		}
		return ans % m;
	}

	public static long pow(long a, long b) {
		long ans = 1;
		while (b > 0) {
			if (b % 2 == 1) ans = ans * a;
			b >>= 1;
			a = a * a;
		}
		return ans;
	}

	public static long gcd(long a, long b) {
		if (b == 0) return a;
		return gcd(b, a % b);
	}
	/**
	 * @param digits : maximum number of digits of PI to be retrieved
	 * @return : value of PI upto max 200 digits and atleast 1 digit.
	 */
	public static String getPI(int digits) {
		if(digits <= 1) return "3";
		return PI.substring(0, Math.min(digits+1, PI.length()));
	}

	/**
	 *
	 * @param n Number to check in O(sqrt(n))
	 * @return true if n is prime
	 */

	public static boolean isPrime(int n) {
		for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
		return true;
	}

	/**
	 *
	 * @param isPrime Sieve. isPrime[i] = true when i is prime, false otherwise
	 */
	public static void sieve(boolean [] isPrime) {
		int n = isPrime.length;
		Arrays.fill(isPrime, true);
		for (int i = 2; i * i < n; ++i) if (isPrime[i]) {
			for (int j = i * i; j < n; j += i) isPrime[j] = false;
		}
		isPrime[0] = isPrime[1] = false;
	}

	public static int countDivisors(int n) {
		int ans = 1;
		for (int i = 2; i * i <= n; ++i) {
			int c = 1;
			while (n % i == 0) {
				c += 1;
				n /= i;
			}
			ans = ans * c;
		}
		if (n > 1) ans *= 2;
		return ans;
	}

	public static int sumDivisors(int n) {
		long ans = 1;
		for (int i = 2; i * i <= n; ++i) {
			int c = i;
			while (n % i == 0) {
				c *= i;
				n /= i;
			}
			ans = (c - 1) / (i - 1) * ans;
		}
		if (n > 1) ans *= (n + 1);
		return (int)ans;
	}
}

