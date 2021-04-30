//package squarefreedivisioneasyversion;

import java.util.*;
import java.io.*;

public class squarefreedivision {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int[] squares = new int[3164];	//stores values of perfect squares.	im dumb, the values can repeat.
		for(int i = 0; i < squares.length; i++) {
			squares[i] = i * i;
		}
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			ArrayList<HashSet<Integer>> sections = new ArrayList<HashSet<Integer>>();
			sections.add(new HashSet<Integer>());
			sections.get(0).add(nums[0]);
			for(int i = 1; i < n; i++) {
				int next = nums[i];
				boolean isValid = true;
				for(int j = 1; j < squares.length; j++) {
					if(squares[j] % next == 0) {
						int test = squares[j] / next;
						if(sections.get(sections.size() - 1).contains(test)) {
							isValid = false;
							break;
						}
					}
					
				}
				if(isValid) {
					sections.get(sections.size() - 1).add(next);
				}
				else {
					sections.add(new HashSet<Integer>());
					sections.get(sections.size() - 1).add(next);
				}
			}
			fout.append(sections.size()).append("\n");
		}
		System.out.print(fout);
	}
}
