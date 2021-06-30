//package savethenature;

import java.util.*;
import java.io.*;

public class savethenature {
	
	static long aBonus, bBonus, a, b, k;
	static Long[] tickets;
	static int[][] bonus;
	
	public static boolean isValid(int val) {	//for a given number of tickets, is it possible to generate k income for ecological progress
		long sum = 0;
		int numBoth = bonus[val - 1][2];
		int numA = bonus[val - 1][0];
		int numB = bonus[val - 1][1];
		int pointer = 0;
		long bothBonus = aBonus + bBonus;
		for(int i = 0; i < numBoth; i++) {
			sum += (tickets[pointer] / 100l) * bothBonus;
			pointer ++;
		}
		for(int i = 0; i < numA; i++) {
			sum += (tickets[pointer] / 100l) * aBonus;
			pointer ++;
		}
		for(int i = 0; i < numB; i++) {
			sum += (tickets[pointer] / 100l) * bBonus;
			pointer ++;
		}
		if(sum >= k) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1223C
		
		//simple binary search solution with greedy
		
		//first notice that you can't directly calculate the answer. Since it is optimal to sell the highest price tickets with the highest bonus, you need to first decide the total amount
		//of tickets that you are going to sell in order to see how many tickets you can sell with the highest bonus.
		//then notice that in order to test whether a certain amount of sold tickets will have a bonus higher than k, is O(n), since you can just pair up the largest tickets with the largest bonus. 
		//put them together, and you have a simple binary search / greedy solution.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			tickets = new Long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				tickets[i] = (long) Integer.parseInt(st.nextToken());
			}
			Arrays.sort(tickets, Collections.reverseOrder());
			st = new StringTokenizer(fin.readLine());
			aBonus = Integer.parseInt(st.nextToken());
			a = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			bBonus = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			if(aBonus < bBonus) {
				long temp = aBonus;
				aBonus = bBonus;
				bBonus = temp;
				temp = a;
				a = b;
				b = temp;
			}
			bonus = new int[n][3];	//for each amount of tickets sold, how many tickets of each type are there
			if(a == 1 && b == 1) {
				bonus[0][2] = 1;
			}
			else if(a == 1) {
				bonus[0][0] = 1;
			}
			else if(b == 1) {
				bonus[0][1] = 1;
			}
			for(int i = 1; i < n; i++) {
				if((i + 1) % a == 0 && (i + 1) % b == 0) {
					bonus[i][2] ++;
				}
				else if((i + 1) % a == 0) {
					bonus[i][0] ++;
				}
				else if((i + 1) % b == 0){
					bonus[i][1] ++;
				}
				bonus[i][0] += bonus[i - 1][0];
				bonus[i][1] += bonus[i - 1][1];
				bonus[i][2] += bonus[i - 1][2];
			}
			k = Long.parseLong(fin.readLine());
			int high = n;
			int low = 1;
			int mid = low + (high - low) / 2;
			int ans = high + 1;
			boolean isValid = false;
			while(low <= high) {
				if(isValid(mid)) {
					if(mid < ans) {
						ans = mid;
						isValid = true;
					}
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			if(isValid) {
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");	
			}
		}
		System.out.print(fout);
	}
}
