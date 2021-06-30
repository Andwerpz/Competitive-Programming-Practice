//package johnnyandcontribution;

import java.util.*;
import java.io.*;

public class johnnyandcontribution {
	public static void main(String[] args) throws IOException {
		
		//1361A
		
		//first, notice that it is always optimal to write the blogs in order of ascending subject number. That way, when you write a higher subject number blog, all of the lower subject
		//number blogs are already written for you. Then it is sufficient to just simulate the situation, writing the blogs in order, and if you ever can't write a certain
		//blog, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		int[] color = new int[n];
		int[][] order = new int[n][];
		st = new StringTokenizer(fin.readLine());
		int orderMax = 0;
		HashSet<Integer> dict = new HashSet<Integer>();	//to check whether all numbers up to the max are contained within the set
		for(int i = 0; i < n; i++) {
			order[i] = new int[2];
			order[i][0] = Integer.parseInt(st.nextToken());
			order[i][1] = i;
			dict.add(order[i][0]);
			orderMax = Math.max(order[i][0], orderMax);
		}
		Arrays.sort(order, (a, b) -> a[0] - b[0]);
		StringBuilder fout = new StringBuilder();
		boolean isValid = true;
		for(int i = 1; i <= orderMax; i++) {
			if(!dict.contains(i)) {
				isValid = false;
				break;
			}
		}
		for(int i = 0; i < n; i++) {
			int max = 0;
			int cur = order[i][1];
			fout.append(cur + 1).append(" ");
			HashSet<Integer> curDict = new HashSet<Integer>();
			for(int j = 0; j < c.get(cur).size(); j++) {
				int next = c.get(cur).get(j);
				curDict.add(color[next]);
				max = Math.max(color[next], max);
			}
			boolean found = false;
			int nextColor = 0;
			for(int j = 1; j <= max; j++) {
				if(!curDict.contains(j)) {
					found = true;
					nextColor = 1;
				}
			}
			if(!found) {
				nextColor = max + 1;
			}
			if(nextColor == order[i][0]) {
				color[cur] = nextColor;
			}
			else {
				isValid = false;
				break;
			}
		}
		System.out.println(isValid? fout : "-1");
	}
}
