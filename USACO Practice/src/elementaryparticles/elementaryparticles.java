//package elementaryparticles;

import java.util.*;
import java.io.*;

public class elementaryparticles {
	public static void main(String[] args) throws IOException {
		
		//1625B
		
		//Notice that in order to make a harmonius subsegment, we only need 1 particle to be of the same type and position. 
		//also notice that as two of the same type particles get closer, you are able to get larger segments. 
		
		//it is easy to see that all you need to find is the two particles that are of the same type and closest. 
		//the answer will be n - (dist of particles). 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashMap<Integer, Integer> v = new HashMap<Integer, Integer>();
			int ans = -1;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(v.containsKey(next)) {
					ans = Math.max(n - Math.abs(v.get(next) - i), ans);
				}
				v.put(next, i);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
