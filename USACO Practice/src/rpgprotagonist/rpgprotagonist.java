//package rpgprotagonist;

import java.util.*;
import java.io.*;

public class rpgprotagonist {
	public static void main(String[] args) throws IOException {
		
		//1400B
		
		//notice that either the swords or warhammers might be lighter than the other. If that is the case, then you always want to prioritize the lighter item, since 
		//they both have the same benefit. To do this, you can start by giving all of the lighter object to one person, then move them one by one to the other person. 
		//for each state, calculate the maximum amount of the heavier object you can take on top of the lighter ones, and take the maximum as the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int count = 0;
		while(t-- > 0) {
			count ++;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int p = Integer.parseInt(st.nextToken());
			int f = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			long sc = Integer.parseInt(st.nextToken());
			long wc = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			long sp = Integer.parseInt(st.nextToken());
			long wp = Integer.parseInt(st.nextToken());
			if(wp < sp) {
				long temp = wp;
				wp = sp;
				sp = temp;
				temp = wc;
				wc = sc;
				sc = temp;
			}
//			System.out.println(p + " " + f);
//			System.out.println(sc + " " + wc);
//			System.out.println(sp + " " + wp);
			long ans = 0;
			long fs = Math.min(sc, f / sp);
			long ps = Math.min(p / sp, sc - fs);
			while(true) {
				//System.out.println("SWORDS: " + (fs + ps));
				long total = fs + ps + Math.min(((f - fs * sp) / wp) + ((p - ps * sp) / wp), wc);
				ans = Math.max(ans, total);
				if(p >= (ps + 1) * sp && fs != 0) {
					ps ++;
					fs --;
				}
				else {
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
