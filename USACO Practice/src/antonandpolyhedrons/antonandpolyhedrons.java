//package antonandpolyhedrons;

import java.util.*;
import java.io.*;

public class antonandpolyhedrons {
	public static void main(String[] args) throws IOException {
		
		//785A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int ans = 0;
		for(int i = 0; i < n; i++) {
			String next = fin.readLine();
			if(next.equals("Tetrahedron")) {
				ans += 4;
			}
			else if(next.equals("Cube")) {
				ans += 6;
			}
			else if(next.equals("Octahedron")) {
				ans += 8;
			}
			else if(next.equals("Dodecahedron")) {
				ans += 12;
			}
			else {
				ans += 20;
			}
		}
		System.out.println(ans);
	}
}
