package modules;

import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;

/**
 * Created by trive on 19-07-2017.
 */
public class ComputePi {
	private static BigDecimal atan(BigDecimal t, MathContext mc, int iter) {
		BigDecimal res = BigDecimal.ZERO;
		BigDecimal arg2 = t.multiply(t, mc);
		for (int i = 0; i < iter; ++i) {
			BigDecimal toUpdate = t.divide(BigDecimal.valueOf(2L*i+1L), mc);
			t = t.multiply(arg2, mc);
			if(i % 2 == 0) res = res.add(toUpdate, mc);
			else res = res.subtract(toUpdate, mc);
		}
		return res;
	}
	static public String computePi(int digits) {
		if (digits <= 1) return "3";
		MathContext mc = new MathContext(digits*2, RoundingMode.HALF_DOWN);
		BigDecimal res = atan(BigDecimal.valueOf(2).divide(BigDecimal.valueOf(11), mc), mc, 2*digits).multiply(BigDecimal.valueOf(2), mc);
		res = res.add(atan(BigDecimal.ONE.divide(BigDecimal.valueOf(7), mc), mc, 2*digits).multiply(BigDecimal.valueOf(3), mc));
		res = res.multiply(BigDecimal.valueOf(4), mc);
		return res.toString().substring(0, digits+1);
	}

	static public void main(String args[]) {
		String res = computePi(200);
		System.out.println(res);
	}
}

