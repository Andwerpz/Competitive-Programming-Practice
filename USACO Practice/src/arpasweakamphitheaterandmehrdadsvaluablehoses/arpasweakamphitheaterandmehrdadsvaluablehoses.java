//package arpasweakamphitheaterandmehrdadsvaluablehoses;

import java.util.*;
import java.io.*;

public class arpasweakamphitheaterandmehrdadsvaluablehoses {
	public static void main(String[] args) throws IOException {
		
		//741B
		
		//you need to keep the total weight under w, while maximizing beauty. This is classic dp problem. One twist is that there are friendship groups, you can only either invite one from the group,
		//or invite all of the group. What you have to do is just consider one group at a time, and treat the group sum of weight and beauty as a separate hose. Considering one group at
		//a time guarantees that you don't double add hoses from the same group.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		int[][] hoses = new int[n][2];	//beauty and weight
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			hoses[i][1] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			hoses[i][0] = Integer.parseInt(st.nextToken());
		}
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
		ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
		HashSet<Integer> v = new HashSet<Integer>();
		for(int i = 0; i < n; i++) {
			if(!v.contains(i)) {
				ArrayDeque<Integer> q = new ArrayDeque<Integer>();
				q.add(i);
				v.add(i);
				groups.add(new ArrayList<Integer>());
				while(q.size() != 0) {
					int next = q.poll();
					groups.get(groups.size() - 1).add(next);
					for(int j = 0; j < c.get(next).size(); j++) {
						if(!v.contains(c.get(next).get(j))) {
							int nextId = c.get(next).get(j);
							q.add(nextId);
							v.add(nextId);
						}
					}
				}
			}
		}
		int[] dp = new int[w + 1];
		Arrays.fill(dp, -1);
		dp[0] = 0;
		for(int i = 0; i < groups.size(); i++) {
			int weightSum = 0;
			int beautySum = 0;
			for(int j = 0; j < groups.get(i).size(); j++) {
				weightSum += hoses[groups.get(i).get(j)][1];
				beautySum += hoses[groups.get(i).get(j)][0];
			}
			for(int j = w; j >= 0; j--) {
				if(dp[j] != -1) {
					for(int k = 0; k < groups.get(i).size(); k++) {
						int weight = hoses[groups.get(i).get(k)][1];
						int beauty = hoses[groups.get(i).get(k)][0];
						if(j + weight <= w) {
							dp[j + weight] = Math.max(dp[j + weight], dp[j] + beauty);
						}
					}
					if(j + weightSum <= w) {
						dp[j + weightSum] = Math.max(dp[j + weightSum], dp[j] + beautySum);
					}
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < dp.length; i++) {
			//System.out.println(dp[i]);
			ans = Math.max(ans, dp[i]);
		}
		System.out.println(ans);
	}
}
