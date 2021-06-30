//package alternativethinking;

import java.util.*;
import java.io.*;

public class alternativethinking {
	public static void main(String[] args) throws IOException {
		
		//was thinking that we first remove the longest subsequence of alternating 1s and 0s. NO!!
		//what you have to recognize is that the answer can be gotten by splitting the string into segments of purely 1s and 0s. 
		//the number of segments is equal to the length of the longest subsequence of alternating 1s and 0s. 
		//The second thing you have to notice is that no matter what bits you flip, you can never get above 2 more than the 
		//original score. You can get two by flipping the middle bit of a run of three or more, flipping the section inbetween two segments with 
		//two consistent numbers. You can get one more if you only have a segment of twos. You just flip it, and everything to one end. If all you have
		//are segments of ones, then you can't do anything to increase your score, since you can't do anything to increase the amount of 
		//segments you have.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		ArrayList<Integer> segments = new ArrayList<Integer>();
		char prev = '3';
		for(int i = 0; i < n; i++) {
			char next = s[i];
			if(i == 0) {
				prev = next;
				segments.add(0);
			}
			else {
				if(prev != next) {
					prev = next;
					segments.add(0);
				}
			}
			segments.set(segments.size() - 1, segments.get(segments.size() - 1) + 1);
		}
		int numTwos = 0;
		int numThrees = 0;
		for(int i = 0; i < segments.size(); i++) {
			if(segments.get(i) == 2) {
				numTwos ++;
			}
			else if(segments.get(i) > 2) {
				numThrees ++;
			}
		}
		if(numThrees >= 1 || numTwos >= 2 || numThrees + numTwos >= 2) {
			System.out.println(segments.size() + 2);
		}
		else if(numTwos == 1) {
			System.out.println(segments.size() + 1);
		}
		else {
			System.out.println(segments.size());
		}
	}
}
