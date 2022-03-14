//package provehimwrong;

import java.util.*;
import java.io.*;

public class provehimwrong {
	public static void main(String[] args) throws IOException {
		
		//1651B
		
		//notice that the sequence 1, 3, 9, 27, ... is the best sequence. Thus, if the given n will make
		//a sequence that has a value above 10^9, then that n is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		ArrayList<Integer> ans = new ArrayList<Integer>();
		long counter = 1;
		ans.add((int) counter);
		while(true) {
			counter *= 3;
			if(counter > 1e9) {
				break;
			}
			ans.add((int) counter);
		}
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			if(n > ans.size()) {
				fout.append("NO\n");
				continue;
			}
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				fout.append(ans.get(i)).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
