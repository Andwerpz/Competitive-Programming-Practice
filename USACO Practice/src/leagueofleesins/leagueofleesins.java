//package leagueofleesins;

import java.util.*;
import java.io.*;

public class leagueofleesins {
	public static void main(String[] args) throws IOException {
		
		//1255C
		
		//i feel that this solution is very roundabout. There must be a better, more direct solution, or maybe my implementation is just bad. 
		
		//i will proceed to write an essay about my solution.
		
		//start with the number only in one group. Add it to the answer and go to the number in that group with only two groups, and designate that second group as the 
		//next group. Add the second and third numbers in the group to the answer. From here on, go to the next designated group, find the one remaining number that isn't
		//included in the answer, and add it. The next group will be the group that the last number is in that only one other number in the group is in, which hasn't
		//been visited yet.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] groups = new int[n - 2][3];
		ArrayList<ArrayList<Integer>> nums = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			nums.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < n - 2; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			groups[i] = new int[] {a, b, c};
			nums.get(a).add(i);
			nums.get(b).add(i);
			nums.get(c).add(i);
		}
		int startNum = 0;
		for(int i = 0; i < n; i++) {
			if(nums.get(i).size() == 1) {
				startNum = i;
				break;
			}
		}
		int startGroup = 0;
		int nextGroup = 0;
		StringBuilder fout = new StringBuilder();
		HashSet<Integer> takenNums = new HashSet<Integer>();
		HashSet<Integer> takenGroups = new HashSet<Integer>();
		takenNums.add(startNum);
		fout.append(startNum + 1).append(" ");
		for(int i = 0; i < groups.length; i++) {
			for(int j = 0; j < 3; j++) {
				if(groups[i][j] == startNum) {
					startGroup = i;
					takenGroups.add(i);
					break;
				}
			}
		}
		for(int i = 0; i < 3; i++) {
			if(nums.get(groups[startGroup][i]).size() == 2) {
				takenNums.add(groups[startGroup][i]);
				fout.append(groups[startGroup][i] + 1).append(" ");
				if(takenGroups.contains(nums.get(groups[startGroup][i]).get(0))) {
					nextGroup = nums.get(groups[startGroup][i]).get(1);
				}
				else {
					nextGroup = nums.get(groups[startGroup][i]).get(0);
				}
			}
		}
		for(int i = 0; i < 3; i++) {
			if(nums.get(groups[startGroup][i]).size() == 3) {
				takenNums.add(groups[startGroup][i]);
				fout.append(groups[startGroup][i] + 1).append(" ");
			}
		}
		for(int i = 1; i < n - 2; i++) {
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			takenGroups.add(nextGroup);
			for(int j = 0; j < 3; j++) {
				int cur = groups[nextGroup][j];
				for(int k = 0; k < nums.get(cur).size(); k++) {
					int g = nums.get(cur).get(k);
					if(!takenGroups.contains(g)) {
						dict.put(g, dict.getOrDefault(g, 0) + 1);
					}
				}
				if(!takenNums.contains(cur)) {
					takenNums.add(cur);
					fout.append(cur + 1).append(" ");
				}
			}
			for(int j : dict.keySet()) {
				if(dict.get(j) == 2 && !takenGroups.contains(j)) {
					nextGroup = j;
					takenGroups.add(j);
				}
			}
		}
		System.out.println(fout);
	}
}
