//package dreamteam;

import java.util.*;
import java.io.*;

public class dreamteam {
	public static void main(String[] args) throws IOException {
		
		//bruh, this has to be written in Kotlin.
		
		//whatever, i'll explain the problem anyways. 
		
		//the goal is to make the maximum value team, that is not the maximum value. To do this, you have to get the minimum positive person, and the maximum negative person, 
		//see which one has the least absolute value, and either remove them or add them to the team, positive one gets removed, and minimum one gets added.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			ArrayList<int[]> pos = new ArrayList<int[]>();	//saving ids and values
			ArrayList<int[]> neg = new ArrayList<int[]>();
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int sum = 0;
			HashSet<Integer> team = new HashSet<Integer>();
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next > 0) {
					pos.add(new int[] {next, i});
					team.add(i);
					sum += next;
				}
				else if(next < 0) {
					neg.add(new int[] {next, i});
				}
			}
			pos.sort((a, b) -> a[0] - b[0]);
			neg.sort((a, b) -> -(a[0] - b[0]));
			if(neg.size() == 0 || pos.get(0)[0] <= -neg.get(0)[0]) {
				team.remove(pos.get(0)[1]);
				sum -= pos.get(0)[0];
			}
			else {
				team.add(neg.get(0)[1]);
				sum += neg.get(0)[0];
			}
			fout.append(sum).append("\n");
			for(int i = 0; i < n; i++) {
				if(team.contains(i)) {
					fout.append("1");
				}
				else {
					fout.append("0");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
