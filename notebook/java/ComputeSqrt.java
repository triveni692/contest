package modules;

import java.math.BigDecimal;
import java.math.BigInteger;

/**
 * Created by trive on 19-07-2017.
 */
public class ComputeSqrt {
	public static String compute(String num, int digits) {
		int idx = num.indexOf('.');
		if(idx != -1) {
			int diff = num.length() - idx;
			if(diff % 2 == 0) {
				num += "0";
				diff += 1;
			}
			num = num.substring(0, idx) + num.substring(idx + 1, num.length());
			diff = (diff - 1) / 2;
			BigDecimal b = new BigDecimal(sqrt(num, digits + diff + 3));
			while(diff > 0) {
				b = b.divide(BigDecimal.TEN);
				diff -= 1;
			}
			return b.toString().substring(0, digits+1);
		}
		if(num.length() % 2 == 1) num = "0" + num;
		return sqrt(num, digits+10).substring(0, digits+1);
	}
	public static String compute(long num, int digits) {
		return compute(Long.toString(num), digits);
	}
	public static String compute(double num, int digits) {
		return compute(Double.toString(num), digits);
	}
	private static String sqrt(String num, int digits) {
		if(num.length() % 2 == 1) return sqrt("0" + num, digits);
		StringBuilder ans = new StringBuilder();
		int i = 0;
		BigInteger q = BigInteger.ZERO;
		BigInteger d = BigInteger.ZERO;
		BigInteger HUNDRED = new BigInteger("100");
		BigInteger [] arr = new BigInteger [10];
		arr[0] = BigInteger.ZERO;
		arr[1] = BigInteger.ONE;
		for (int j =2; j < 10; ++j) arr[j] = BigInteger.valueOf(j);

		while (digits > 0) {
			d = d.multiply(HUNDRED);
			q = q.multiply(BigInteger.TEN);
			if(i < num.length()) {
				d = d.add(new BigInteger(num.substring(i, i+2)));
			}
			int l = 0, r = 9, mid;
			while (r > l) {
				mid = (l + r + 1) / 2;
				if(q.add(arr[mid]).multiply(arr[mid]).compareTo(d) <= 0) l = mid;
				else r = mid - 1;
			}
			if(i == num.length()) ans.append('.');
			ans.append(Integer.toString(l));
			q = q.add(arr[l]);
			d = d.subtract(q.multiply(arr[l]));
			q = q.add(arr[l]);
			i += 2;
			digits -= 1;
		}
		return ans.toString();
	}

	static public void main(String [] args) {
		System.out.println(compute("3", 100) + " " + Math.sqrt(3));
	}
}

