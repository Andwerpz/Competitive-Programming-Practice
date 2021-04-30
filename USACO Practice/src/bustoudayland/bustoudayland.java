//package bustoudayland;

import java.util.*;
import java.io.*;

public class bustoudayland {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[][] b = new char[n][5];
		boolean isValid = false;
		for(int i = 0; i < n; i++) {
			b[i] = fin.readLine().toCharArray();
			if(b[i][0] == 'O' && b[i][1] == 'O' && !isValid) {
				b[i][0] = '+';
				b[i][1] = '+';
				isValid = true;
			}
			if(b[i][3] == 'O' && b[i][4] == 'O' && !isValid) {
				b[i][3] = '+';
				b[i][4] = '+';
				isValid = true;
			}
		}
		StringBuilder fout = new StringBuilder();
		if(isValid) {
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				fout.append(String.valueOf(b[i])).append("\n");
			}
		}
		else {
			fout.append("NO\n");
		}
		System.out.print(fout);
	}
}
