package teambuilding;

import java.util.*;
import java.io.*;

public class teambuilding {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		boolean isValid = false;
		outer:
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int first = 0;
			for(int j = 0; j < k; j++) {
				if(j == 0) {
					first = Integer.parseInt(st.nextToken());
				}
				else {
					if(first != Integer.parseInt(st.nextToken())) {
						isValid = true;
						break outer;
					}
				}
			}
		}
		System.out.println(isValid? "YES" : "NO");
	}
}
