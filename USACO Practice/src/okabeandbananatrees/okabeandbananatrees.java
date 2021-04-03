//package okabeandbananatrees;

import java.util.*;
import java.io.*;

public class okabeandbananatrees {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int m = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		long x = 0;
		long y = b;
		long vert = 0;
		long horiz = 0;
		for(int i = 0; i <= b; i++) {
			vert += i;
		}
		long max = 0;
		//System.out.println(vert);
		for(int i = 0; i <= b; i++) {
			//System.out.println(vert + " " + horiz + " " + (vert * (x + 1) + horiz * (y + 1)));
			if(vert * (x + 1) + horiz * (y + 1) > max) {
				max = vert * (x + 1) + horiz * (y + 1);
			}
			for(int j = i * m + 1; j <= (i + 1) * m; j++) {
				horiz += j;
			}
			vert -= b - i;
			x += m;
			y -= 1;
		}
		System.out.println(max);
	}
}
