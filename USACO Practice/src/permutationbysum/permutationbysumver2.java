package permutationbysum;

import java.util.*;
import java.io.*;

public class permutationbysumver2 {
	public static void main(String[] args) throws IOException {
		
		//1512E
		
				//We are tasked with making a permutation of numbers from 1 - n, with the numbers in the indicies between l and r inclusive adding up to sum s.
				//first, lets define the number of numbers you can choose, l - r + 1 = k. The minimum sum that you can choose from a permutation is the first smallest
				//k numbers, and the maximum sum is the biggest k numbers. You can easily see that it is possible to make every number inbetween the lowest and highest 
				//sums as well. So all you have to do is figure out where the sum lies. If it is inside the range, then you can make it, but if it isn't in the range, then you can't make it.
				
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			int s = Integer.parseInt(st.nextToken());
			int k = r - l + 1;
			int low = 0;
			int high = 0;
			for(int i = 1; i <= k; i++) {
				low += i;
			}
			for(int i = n - k + 1; i <= n; i++) {
				high += i;
			}
			if(s >= low && s <= high) {
				 int base = (s - low) / k;
				 int remainder = (s - low) % k;
				 HashSet<Integer> sumPart = new HashSet<Integer>();
				 HashSet<Integer> notSum = new HashSet<Integer>();
				 for(int i = k + base; i > base; i--) {
					 if(remainder > 0) {
						 sumPart.add(i + 1);
						 remainder --;
					 }
					 else {
						 sumPart.add(i);
					 }
				 }
				 for(int i = 1; i <= n; i++) {
					 if(!sumPart.contains(i)) {
						 notSum.add(i);
					 }
				 }
				 System.out.println(sumPart);
				 System.out.println("BASE: " + base + " REMAINDER: " + remainder);
				 for(int i = 0; i < n; i++) {
					 if(i >= l && i <= r) {
						 int next = sumPart.iterator().next();
						 fout.append(next).append(" ");
						 sumPart.remove(next);
						 //System.out.println("SUM: " + next);
					 }
					 else {
						 int next = notSum.iterator().next();
						 fout.append(next).append(" ");
						 notSum.remove(next);
						 //System.out.println("NOT SUM: " + next);
					 }
				 }
				 fout.append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
