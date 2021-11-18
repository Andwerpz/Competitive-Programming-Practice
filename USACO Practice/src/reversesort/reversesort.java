//package reversesort;

import java.util.*;
import java.io.*;

public class reversesort {
	public static void main(String[] args) throws IOException {
		
		//1605B
		
		//notice that after you sort the numbers, there will be a region of only 1s and a region of only 0s. If you choose all 0s that 
		//are initially in the 1s section, and all the 1s that are in the 0s section, and swap them, then the list will be sorted. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			int numOnes = 0;
			for(char i : s) {
				if(i == '1') {
					numOnes ++;
				}
			}
			ArrayList<Integer> operation = new ArrayList<Integer>();
			for(int i = n - numOnes; i < n; i++) {
				if(s[i] == '0') {
					operation.add(i + 1);
				}
			}
			for(int i = 0; i < n - numOnes; i++) {
				if(s[i] == '1') {
					operation.add(i + 1);
				}
			}
			if(operation.size() == 0) {
				fout.append("0").append("\n");
			}
			else {
				fout.append(1).append("\n");
				fout.append(operation.size()).append(" ");
				operation.sort((a, b) -> Integer.compare(a, b));
				for(int i : operation) {
					fout.append(i).append(" ");
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
