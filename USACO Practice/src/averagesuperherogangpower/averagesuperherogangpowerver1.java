//package averagesuperherogangpower;

import java.util.*;
import java.io.*;

public class averagesuperherogangpowerver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		Double[] nums = new Double[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Double.parseDouble(st.nextToken());
		}
		Arrays.sort(nums, (a, b) -> -Double.compare(a, b));
		double[] pfx = new double[n];
		double sum = 0;
		for(int i = 0; i < n; i++) {
			sum += nums[i];
			pfx[i] = sum;
			//System.out.print(pfx[i] + " ");
		}
		//System.out.println();
		double ans = 0;
		int pointer = n - 1;
		double curM = m;
		for(int i = 0; i <= Math.min(m, n - 1); i++) {
			double cur = (pfx[pointer] + Math.min(curM, (n - i) * k)) / (double) (n - i);
			ans = Math.max(ans, cur);
			//System.out.println(cur + " " + pointer + " " + curM);
			pointer --;
			curM --;
		}
		System.out.println(ans);
	}
}
