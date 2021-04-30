//package hamburgers;

import java.util.*;
import java.io.*;

public class hamburgers {
	
	static int pb;
	static int ps;
	static int pc;
	
	public static boolean isValid(long target, int nb, int ns, int nc, int numB, int numS, int numC, int cost, long money) {
		//System.out.println(money + " " + target);
		long sum = 0;
		while(true) {
			//System.out.println(money + " " + nb + " " + ns + " " + nc);
			if((nb == 0 && ns == 0 && nc == 0) || (numB == 0 && numS == 0 && nc == 0) || (numB == 0 && ns == 0 && numC == 0) || (nb == 0 && numS == 0 && numC == 0) ||
					(numB == 0 && ns == 0 && nc == 0) || (nb == 0 && ns == 0 && numC == 0) || (nb == 0 && numS == 0 && nc == 0)) {
				sum += money / cost;
				break;
			}
			else {
				int curCost = cost;
				if(nb != 0) {
					if(numB >= nb) {
						curCost -= nb * pb;
						nb = 0;
					}
					else {
						curCost -= numB * pb;
						nb -= numB;
					}
				}
				if(ns != 0) {
					if(numS >= ns) {
						curCost -= ns * ps;
						ns = 0;
					}
					else {
						curCost -= numS * ps;
						ns -= numS;
					}
				}
				if(nc != 0) {
					if(numC >= nc) {
						curCost -= nc * pc;
						nc = 0;
					}
					else {
						curCost -= numC * pc;
						nc -= numC;
					}
				}
				money -= curCost;
				sum ++;
			}
			if(money < 0) {
				sum -= 1;
				break;
			}
			if(money == 0) {
				break;
			}
		}
		if(sum >= target) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] burg = fin.readLine().toCharArray();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int nb = Integer.parseInt(st.nextToken());
		int ns = Integer.parseInt(st.nextToken());
		int nc = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		pb = Integer.parseInt(st.nextToken());
		ps = Integer.parseInt(st.nextToken());
		pc = Integer.parseInt(st.nextToken());
		int numB = 0;
		int numS = 0;
		int numC = 0;
		int cost = 0;
		int firstCost = 0;
		for(int i = 0; i < burg.length; i++) {
			cost += burg[i] == 'B'? pb : burg[i] == 'S'? ps : pc;
			numB += burg[i] == 'B'? 1 : 0;
			numS += burg[i] == 'S'? 1 : 0;
			numC += burg[i] == 'C'? 1 : 0;
		}
		long money = Long.parseLong(fin.readLine());
		long low = 0;
		long high = Long.MAX_VALUE / 1000;
		long mid = low + (high - low) / 2;
		long ans = low;
		while(low <= high) {
			//System.out.println(low + " " + high + " " + mid);
			if(isValid(mid, nb, ns, nc, numB, numS, numC, cost, money)) {
				if(ans < mid) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
