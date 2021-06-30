//package antonanddigits;

import java.util.*;
import java.io.*;

public class antonanddigits {
	public static void main(String[] args) throws IOException {
		
		//734B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int twos = Integer.parseInt(st.nextToken());
		int threes = Integer.parseInt(st.nextToken());
		int fives = Integer.parseInt(st.nextToken());
		int sixes = Integer.parseInt(st.nextToken());
		int ans = 0;
		int numBig = Math.min(twos, Math.min(fives, sixes));
		ans += numBig * 256;
		twos -= numBig;
		ans += Math.min(twos, threes) * 32;
		System.out.println(ans);
	}
}
