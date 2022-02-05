//package killthemonster;

import java.util.*;
import java.io.*;

public class killthemonster {
	
	public static boolean win(long ka, long kw, long w, long a, long ch, long cd, long mh, long md) {
		ch += ka * a;
		cd += kw * w;
		long turnsToKill = mh / cd + (mh % cd == 0? 0 : 1);
		long turnsToDie = ch / md + (ch % md == 0? 0 : 1);
		if(turnsToDie < turnsToKill) {
			return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			Long ch = Long.parseLong(st.nextToken());
			Long cd = Long.parseLong(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			long mh = Long.parseLong(st.nextToken());
			long md = Long.parseLong(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			long k = Long.parseLong(st.nextToken());
			long w = Long.parseLong(st.nextToken());
			long a = Long.parseLong(st.nextToken());
			boolean isValid = false;
			for(int i = 0; i <= k; i++) {
				if(win(i, k - i, w, a, ch, cd, mh, md)) {
					//System.out.println(i);
					isValid = true;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
