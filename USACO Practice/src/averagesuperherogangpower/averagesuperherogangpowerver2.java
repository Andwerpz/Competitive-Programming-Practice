package averagesuperherogangpower;

import java.util.*;
import java.io.*;

public class averagesuperherogangpowerver2 {
	public static void main(String[] args) throws IOException {
		
		//1111B
		
				//huh, pulled this off of u_kraken. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		double[] a = new double[n];
		for (int i = 0; i < n; i++) {
			a[i] = Double.parseDouble(st.nextToken());
	 	}
	 	Arrays.sort(a);
	 	double tot = 0, res = 0, sum = 0;
	 	for (int i = n - 1; i >= 0; i--) {
		 tot += a[i];
    sum += k;
	    if (i <= m)
	      res = Math.max(res, (tot + Math.min(sum, m - i)) / (n - i));
	  }
		System.out.println(res);
	}
}
