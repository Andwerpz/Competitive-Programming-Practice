//package xeniaandcolorfulgems;

import java.util.*;
import java.io.*;

public class xeniaandcolorfulgems {
	
	public static long getMin(long[] a, long[] b, long[] c) {
		int pa = 0;
		int pc = 0;
		long min = Long.MAX_VALUE;
		for(int i = 0; i < b.length; i++) {
			long next = b[i];
			while(pa + 1 != a.length && a[pa + 1] <= next) {
				pa ++;
			}
			while(pc + 1 != c.length && c[pc] < next) {
				pc ++;
			}
			if(a[pa] <= next && next <= c[pc]) {
				long da = a[pa] - next;
				long db = next - c[pc];
				long dc = c[pc] - a[pa];
				min = Math.min(min, da * da + db * db + dc * dc);
			}
		}
		//System.out.println(min);
		return min;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1336B
		
		//pretty much just try all combos, using one list of gems as the anchor.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int nr = Integer.parseInt(st.nextToken());
			int ng = Integer.parseInt(st.nextToken());
			int nb = Integer.parseInt(st.nextToken());
			long[] r = new long[nr];
			long[] g = new long[ng];
			long[] b = new long[nb];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < nr; i++) {
				r[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < ng; i++) {
				g[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < nb; i++) {
				b[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(r);
			Arrays.sort(g);
			Arrays.sort(b);
			long ans = Long.MAX_VALUE;
			ans = Math.min(ans, getMin(r, g, b));
			ans = Math.min(ans, getMin(r, b, g));
			ans = Math.min(ans, getMin(g, r, b));
			ans = Math.min(ans, getMin(g, b, r));
			ans = Math.min(ans, getMin(b, g, r));
			ans = Math.min(ans, getMin(b, r, g));
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
