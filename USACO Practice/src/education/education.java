//package education;

import java.util.*;
import java.io.*;

public class education {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			//System.out.println("COST--- " + c);
			int[] profit = new int[n];
			int[] moveCost = new int[n - 1];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				profit[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n - 1; i++) {
				moveCost[i] = Integer.parseInt(st.nextToken());
			}
			long low = -1;
			int curMoney = 0;
			long curDays = 0;
			int curPos = 0;
			for(int i = 0; i < n; i++) {
				//System.out.println(curPos + " " + curDays + " " + curMoney);
				long curDaysLeft = (long) Math.ceil((double)(c - curMoney) / profit[curPos]) + curDays;
				if(low == -1 || curDaysLeft < low) {
					low = curDaysLeft;
				}
				if(i + 1 < n) {
					int cost = moveCost[i];
					int moveDays = (int) Math.ceil((double)(cost - curMoney) / profit[curPos]);
					curMoney = moveDays * profit[curPos] + curMoney - cost;
					curPos ++;
					curDays += moveDays + 1;
					//System.out.println("move days : " + moveDays);
					//System.out.println("move cost : " + cost);
				}
			}
			fout.append(low + "\n");
		}
		System.out.print(fout);
	}
}
