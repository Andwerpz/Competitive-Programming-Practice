//package phoenixanddistribution;

import java.util.*;
import java.io.*;

public class phoenixanddistribution {
	public static void main(String[] args) throws IOException {
		
		//1348C
		
		//lots of heuristics
		
		//if the initial string consists of only 1 character, then the answer is to divide them into k equal strings, or as close to equal as you can get them.
		
		//if the inital string consists of exactly two sets of k different characters, then the answer is to divide them into k strings, each with one character of each type.
		
		//pls, look at tutorial, or code. Idk really why this works
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int[] charCount = new int[26];
			for(int i = 0; i < n; i++) {
				charCount[s[i] - 'a'] ++;
			}
			boolean divisible = true;
			boolean seen = false;
			boolean seen2 = false;
			for(int i = 0; i < charCount.length; i++) {
				if(charCount[i] != 0 && charCount[i] != k) {
					divisible = false;
					break;
				}
				else if(charCount[i] == k) {
					if(seen2) {
						divisible = false;
						break;
					}
					else if(seen) {
						seen2 = true;
					}
					else {
						seen = true;
					}
				}
			}
			if(divisible) {
				for(int i = 0; i < charCount.length; i++) {
					if(charCount[i] != 0) {
						fout.append((char)(i + 'a'));
					}
				}
				fout.append("\n");
			}
			else {
				char minimumChar = 'a';
				char maximumChar = 'a';
				int pointer = 0;
				int counter = 0;
				while(counter != k) {
					while(pointer != 26 && charCount[pointer] == 0) {
						pointer ++;
					}
					if(pointer == 26) {
						break;
					}
					if(counter == 0) {
						minimumChar = (char) (pointer + 'a');
					}
					counter ++;
					charCount[pointer] --;
					maximumChar = (char) (pointer + 'a');
				}
				if(maximumChar != minimumChar) {
					fout.append(maximumChar).append("\n");
				}
				else {
					fout.append(minimumChar);
					boolean allSame = true;
					seen = false;
					int index = 0;
					for(int i = 0; i < charCount.length; i++) {
						if(charCount[i] != 0) {
							if(seen) {
								allSame = false;
								break;
							}
							else {
								seen = true;
								index = i;
							}
						}
					}
					if(allSame) {
						int amt = charCount[index];
						for(int i = 0; i < amt / k + (amt % k != 0? 1 : 0); i++) {
							fout.append((char) (index + 'a'));
						}
					}
					else {
						while(pointer != 26) {
							while(pointer != 26 && charCount[pointer] == 0) {
								pointer ++;
							}
							if(pointer == 26) {
								break;
							}
							fout.append((char) (pointer + 'a'));
							charCount[pointer] --;
						}
					}
					fout.append("\n");
				}
				
			}
		}
		System.out.print(fout);
	}
}
