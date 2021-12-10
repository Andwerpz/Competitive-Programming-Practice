//package messages;

import java.util.*;
import java.io.*;

public class messages {
	public static void main(String[] args) throws IOException {
		
		//1612E
		
		//to solve this problem, you need to figure a upper limit to the amount of messages that you can pin, and search the remaining
		//amounts for the best solution. 
		
		//to search a given amount of messages is an O(n*log(n)) process. First go through each message, and compute the expected 
		//messages read for that message given that it's pinned. Then sort the messages, and take the top ones. 
		
		//the trick is to notice that the maximum amount of pinned messages anyone is willing to read is 20, and pinning
		//more than 20 messages is always a bad idea, because as soon as you pin the 21st message, all the messages from before
		//will lose value.
		
		//so to solve, just search the message amounts from 1 - 20, and take the maximum. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		HashMap<Integer, ArrayList<Integer>> m = new HashMap<Integer, ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int next = Integer.parseInt(st.nextToken());
			int val = Integer.parseInt(st.nextToken());
			if(!m.containsKey(next)) {
				m.put(next, new ArrayList<Integer>());
			}
			m.get(next).add(val);
		}
		//System.out.println(m);
		double maxExp = 0;
		ArrayList<Integer> ans = new ArrayList<Integer>();
		for(int i = 1; i <= Math.min(20, m.size()); i++) {
			double[][] order = new double[m.size()][2];	//message index, expected value
			int c = 0;
			for(int j : m.keySet()) {
				ArrayList<Integer> nums = m.get(j);
				order[c][0] = j;
				for(int k = 0; k < nums.size(); k++) {
					order[c][1] += Math.min(1d, ((double) nums.get(k)) / ((double) i));
					//System.out.println(((double) nums.get(k)) / ((double) i));
				}
				c++;
			}
			Arrays.sort(order, (a, b) -> -Double.compare(a[1], b[1]));	//sort by descending expected value
			double curExp = 0;
			ArrayList<Integer> curAns = new ArrayList<Integer>();
			for(int j = 0; j < i; j++) {
				curExp += order[j][1];
				curAns.add((int) order[j][0]);
			}
			//System.out.println(curAns + " " + curExp);
			if(curExp > maxExp) {
				ans = curAns;
				maxExp = curExp;
			}
		}
		fout.append(ans.size()).append("\n");
		for(int i : ans) {
			fout.append(i).append(" ");
		}
		fout.append("\n");
		System.out.println(fout);
	}
}
