package giftset;

import java.util.*;
import java.io.*;

public class giftsetver1 {
	
	public static int getAmt(int x, int y, int a, int b) {
		return Math.min(x / a, y / b);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int high = Math.min(x / a, y / b);
			int low = 1;
			int mid = low + (high - low) / 2;
			int ans = 0;
			while(low <= high) {
				int nextX = x - (a * mid);
				int nextY = y - (b * mid);
				int cur = mid + getAmt(nextY, nextX, a, b);
				int prev = mid + getAmt(nextY + b, nextX + a, a, b) - 1;
				System.out.println(mid + " " + nextX + " " + nextY + " " + cur + " " + prev);
				if(cur >= prev) {
					ans = Math.max(cur, ans);
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			if(high == 0) {
				ans = Math.min(x / b, y / a);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
