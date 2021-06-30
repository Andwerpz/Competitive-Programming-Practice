//package compressionandexpansion;

import java.util.*;
import java.io.*;

public class compressionandexpansion {
	public static void main(String[] args) throws IOException {
		
		//1523C
		
		//instead of being dumb and using an array with a pointer, just use a stack. much easier that way
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			ArrayList<Integer> s = new ArrayList<Integer>();
			int n = Integer.parseInt(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(fin.readLine());
				if(next == 1) {
					s.add(1);
				}
				else {
					while(s.get(s.size() - 1) != next - 1) {
						s.remove(s.size() - 1);
					}
					s.set(s.size() - 1, next);
				}
				for(int j = 0; j < s.size(); j++) {
					fout.append(s.get(j));
					if(j != s.size() - 1) {
						fout.append(".");
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
