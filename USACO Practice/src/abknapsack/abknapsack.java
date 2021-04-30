//package abknapsack;

import java.util.*;
import java.io.*;

public class abknapsack {
	public static void main(String[] args) throws IOException {
		
		//every time we want to add an item into the knapsack, we see how much value we will get from just filling the knapsack with each weight group.
		//then we choose the top from the weight group with the most value
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		long s = Integer.parseInt(st.nextToken());
		long a = Integer.parseInt(st.nextToken());
		long b = Integer.parseInt(st.nextToken());
		int[] aItems = new int[n];
		int[] bItems = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			aItems[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			bItems[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(aItems);
		Arrays.sort(bItems);
		long aSum = 0;
		long bSum = 0;
		int aLow = (int) (n - 1 - Math.min(n - 1, s / a));
		int bLow = (int) (m - 1 - Math.min(m - 1, s / b));
		int aHigh = n - 1;
		int bHigh = m - 1;
		long ans = 0;
		for(int i = aLow; i < n; i++) {
			aSum += aItems[i];
		}
		for(int i = bLow; i < m; i++) {
			bSum += bItems[i];
		}
		while(true) {
			if((s - a < 0 && s - b < 0) || (aHigh == -1 && bHigh == -1)) {
				break;
			}
			if(aSum >= bSum && aHigh != -1) {
				s -= a;
				ans += aItems[aHigh];
				aSum -= aItems[aHigh];
				aHigh --;
			}
			else if(bSum > aSum && bHigh != -1) {
				s -= b;
				ans += bItems[bHigh];
				bSum -= bItems[bHigh];
				bHigh --;
			}
			while(aHigh - aLow + 1 > s / a && aLow < n) {
				aSum -= aItems[aLow];
				aLow ++;
			}
			while(bHigh - bLow + 1 > s / b && bLow < m) {
				bSum -= bItems[bLow];
				bLow ++;
			}
		}
		System.out.println(ans);
	}
}
