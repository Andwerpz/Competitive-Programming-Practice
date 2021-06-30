//package evenoddgame;

import java.util.*;
import java.io.*;

public class evenoddgame {
	public static void main(String[] args) throws IOException {
		
		//1427D
		
		//alice and bob have two motives each, with equal priority: maximize their own score and minimize the other persons score. Thus, for their turn, they should
		//always take the maximum number possible. If it can add to their score, then they are satisfying their first motive, and if it doesn't add to their
		//score, then it satisfies the second motive.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			PriorityQueue<Integer> evens = new PriorityQueue<Integer>((a, b) -> -Integer.compare(a, b));
			PriorityQueue<Integer> odds = new PriorityQueue<Integer>((a, b) -> -Integer.compare(a, b));
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next % 2 == 0) {
					evens.add(next);
				}
				else {
					odds.add(next);
				}
			}
			boolean aliceTurn = true;
			long aliceScore = 0;
			long bobScore = 0;
			while(evens.size() + odds.size() != 0) {
				//System.out.println(evens.peek() + " " + odds.peek());
				if(aliceTurn) {
					if(evens.size() != 0 && odds.size() != 0) {
						if(evens.peek() > odds.peek()) {
							aliceScore += evens.poll();
						}
						else {
							odds.poll();
						}
					}
					else if(evens.size() != 0) {
						aliceScore += evens.poll();
					}
					else {
						odds.poll();
					}
				}
				else {
					if(evens.size() != 0 && odds.size() != 0) {
						if(evens.peek() > odds.peek()) {
							evens.poll();
						}
						else {
							bobScore += odds.poll();
						}
					}
					else if(evens.size() != 0) {
						evens.poll();
					}
					else {
						bobScore += odds.poll();
					}
				}
				aliceTurn = !aliceTurn;
			}
			//System.out.println(aliceScore + " " + bobScore);
			if(aliceScore > bobScore) {
				fout.append("Alice\n");
			}
			else if(bobScore > aliceScore) {
				fout.append("Bob\n");
			}
			else {
				fout.append("Tie\n");
			}
		}
		System.out.print(fout);
	}
}
