package abknapsack;

import java.util.*;
import java.io.*;

public class abknapsackver2 {
	public static void main(String[] args) throws IOException {
		
		//ITMO course AB knapsack
		
		//basically, you have two groups. All you need to do is first prioritize the highest cost items of one group, and one by one remove them. Then, when the weight
		//permits, add the items from the second group prioritizing cost.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int s = Integer.parseInt(st.nextToken());
		int aWeight = Integer.parseInt(st.nextToken());
		int bWeight = Integer.parseInt(st.nextToken());
		long[] a = new long[n];
		long[] b = new long[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			b[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(a);
		Arrays.sort(b);
		
		for(int i = a.length - 2; i >= 0; i--) {
			a[i] += a[i + 1];
		}
		for(int i = b.length - 2; i >= 0; i--) {
			b[i] += b[i + 1];
		}
		long weight = (a.length + 1) * aWeight;
		int pointer = b.length;
		long ans = 0;
		for(int i = 0; i <= a.length; i++) {
			weight -= aWeight;
			long aCost = i != a.length? a[i] : 0;
			long bCost = 0;
			while(pointer - 1 != -1 && weight + bWeight <= s) {
				pointer -= 1;
				weight += bWeight;
			}
			bCost = pointer == b.length? 0 : b[pointer];
			if(weight <= s) {
				ans = Math.max(aCost + bCost, ans);
			}
		}
		System.out.println(ans);
	}
}
