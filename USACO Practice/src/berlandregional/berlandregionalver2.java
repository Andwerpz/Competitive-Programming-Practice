package berlandregional;

import java.util.*;
import java.io.*;

public class berlandregionalver2 {
	public static void main(String[] args) throws IOException {
		
		//this solution is... a slight upgrade to my original solution. The backbone is much clearer than the other one
		//the main optimization is that once i see that i can't pull any more teams from a university, given a team size, 
		//i don't query it for larger team sizes. Also i don't waste memory on storing universities with no people in them.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			//int[] uniSizes = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] uniList = new int[n];
			HashMap<Integer, Integer> uniMap = new HashMap<Integer, Integer>();
			int numUnique = 0;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(!uniMap.containsKey(next)) {
					uniMap.put(next, numUnique);
					numUnique ++;
				}
				uniList[i] = next;
				//uniSizes[next] += 1;
			}
			st = new StringTokenizer(fin.readLine());
			ArrayList<ArrayList<Integer>> teams = new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Long>> pfx = new ArrayList<ArrayList<Long>>();
			for(int i = 0; i < numUnique; i++) {
				teams.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				int index = uniMap.get(uniList[i]);
				teams.get(index).add(next);
			}
			for(int i = 0; i < teams.size(); i++) {
				teams.get(i).sort((a, b) -> -Integer.compare(a, b));
			}
			for(int i = 0; i < teams.size(); i++) {
				pfx.add(new ArrayList<Long>());
				long sum = 0;
				for(int j = 0; j < teams.get(i).size(); j++) {
					sum += teams.get(i).get(j);
					pfx.get(i).add(sum);
				}
			}
			HashSet<Integer> validTeams = new HashSet<Integer>();
			for(int i = 0; i < teams.size(); i++) {
				validTeams.add(i);
			}
			for(int i = 1; i <= n; i++) {
				long sum = 0;
				HashSet<Integer> valid = new HashSet<Integer>();
				for(int k : validTeams) {
					if(teams.get(k).size() < i) {	//the uni can't send a team
						continue;
					}
					else {
						valid.add(k);
						int numPeople = teams.get(k).size() / i;
						numPeople *= i;
						sum += pfx.get(k).get(numPeople - 1);
					}
				}
				validTeams = valid;
				fout.append(sum).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
