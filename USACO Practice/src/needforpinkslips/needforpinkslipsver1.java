package needforpinkslips;

import java.util.*;
import java.io.*;
import java.math.BigDecimal;

public class needforpinkslipsver1 {
	
	static BigDecimal v;
	
	public static BigDecimal getAns(BigDecimal c, BigDecimal m, BigDecimal p, BigDecimal total, int layer) {
		//System.out.println(c + " " + m + " " + p + " " + layer + " " + total);
		//System.out.println(total.doubleValue());
		if(total.doubleValue() < Math.pow(10, -6)) {
			//System.out.println(total.doubleValue());
			return new BigDecimal(0);
		}
		//System.out.println(p.doubleValue() + " " + (layer + 1) + " " + total);
		BigDecimal ans = new BigDecimal("1").multiply(p).multiply(new BigDecimal(layer + 1)).multiply(total);
		if(p.doubleValue() >= 1) {
			return ans;
		}
		//System.out.println(ans);
		if(c.doubleValue() > 0) {
			if(c.doubleValue() < v.doubleValue()) {
				BigDecimal newC = new BigDecimal(-1);
				BigDecimal newM = new BigDecimal(m.toString());
				BigDecimal newP = new BigDecimal(p.toString());
				BigDecimal newTotal = new BigDecimal(total.toString()).multiply(c);
				if(m.doubleValue() > 0) {
					newM = newM.add(c.divide(new BigDecimal(2)));
					newP = newP.add(c.divide(new BigDecimal(2)));
				}
				else {
					newP = newP.add(c);
				}
				ans = ans.add(getAns(newC, newM, newP, newTotal, layer + 1));
			}
			else {
				BigDecimal newC = new BigDecimal(c.toString()).subtract(v);
				BigDecimal newM = new BigDecimal(m.toString());
				BigDecimal newP = new BigDecimal(p.toString());
				BigDecimal newTotal = new BigDecimal(total.toString()).multiply(c);
				if(m.doubleValue() > 0) {
					newM = newM.add(v.divide(new BigDecimal(2)));
					newP = newP.add(v.divide(new BigDecimal(2)));
				}
				else {
					newP = newP.add(v);
				}
				ans = ans.add(getAns(newC, newM, newP, newTotal, layer + 1));
			}
		}
		if(m.doubleValue() > 0) {
			if(m.doubleValue() < v.doubleValue()) {
				BigDecimal newC = new BigDecimal(c.toString());
				BigDecimal newM = new BigDecimal(-1);
				BigDecimal newP = new BigDecimal(p.toString());
				BigDecimal newTotal = new BigDecimal(total.toString()).multiply(m);
				if(c.doubleValue() > 0) {
					newC = newC.add(m.divide(new BigDecimal(2)));
					newP = newP.add(m.divide(new BigDecimal(2)));
				}
				else {
					newP = newP.add(m);
				}
				ans = ans.add(getAns(newC, newM, newP, newTotal, layer + 1));
			}
			else {
				BigDecimal newC = new BigDecimal(c.toString());
				BigDecimal newM = new BigDecimal(m.toString()).subtract(v);
				BigDecimal newP = new BigDecimal(p.toString());
				BigDecimal newTotal = new BigDecimal(total.toString()).multiply(m);
				if(c.doubleValue() > 0) {
					newC = newC.add(v.divide(new BigDecimal(2)));
					newP = newP.add(v.divide(new BigDecimal(2)));
				}
				else {
					newP = newP.add(v);
				}
				ans = ans.add(getAns(newC, newM, newP, newTotal, layer + 1));
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			double c = Double.parseDouble(st.nextToken());
			double m = Double.parseDouble(st.nextToken());
			double p = Double.parseDouble(st.nextToken());
			v = new BigDecimal(Double.parseDouble(st.nextToken()));
			fout.append(getAns(new BigDecimal(c), new BigDecimal(m), new BigDecimal(p), new BigDecimal(1), 0)).append("\n");
		}
		System.out.print(fout);
	}
}
