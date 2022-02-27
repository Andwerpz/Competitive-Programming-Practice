package redistributinggifts;

import java.util.*;
import java.io.*;

public class redistributinggifts {
	public static void main(String[] args) throws IOException {
		
		//USACO Silver 2022 February
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] nums = new int[n][n];
		ArrayList<HashSet<Integer>> pref = new ArrayList<HashSet<Integer>>();
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < n; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
			}
			pref.add(new HashSet<Integer>());
			int curGift = i + 1;
			for(int j = 0; j < n; j++) {
				if(nums[i][j] == curGift) {
					break;
				}
				pref.get(i).add(nums[i][j]);
			}
		}
		//for each cow, which component is it in
		HashMap<Integer, Integer> cowComponent = new HashMap<Integer, Integer>();
		boolean[] v = new boolean[n];
		for(int i = 0; i < n; i++) {
			if(v[i]) {
				continue;
			}
			Stack<Integer> s = new Stack<Integer>();
			v[i] = true;
			s.add(i + 1);
			int curComponent = i;
			while(s.size() != 0) {
				int curCow = s.pop();
				cowComponent.put(curCow, curComponent);
				for(int j : pref.get(curCow - 1)) {
					if(!v[j - 1]) {
						s.add(j);
						v[j - 1] = true;
					}
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			int curGift = i + 1;
			HashSet<Integer> tradeableComponents = new HashSet<Integer>();
			//figure out who can trade
			for(int j = 0; j < n; j++) {
				if(pref.get(j).contains(curGift)) {
					tradeableComponents.add(cowComponent.get(j + 1));
				}
			}
			System.out.println(tradeableComponents);
			for(int j = 0; j < n; j++) {
				int nextGift = nums[i][j];
				if(nextGift == curGift) {
					break;
				}
				int nextComponent = cowComponent.get(nextGift);
				if(tradeableComponents.contains(nextComponent)) {
					curGift = nextGift;
					break;
				}
			}
			fout.append(curGift).append("\n");
		}
		System.out.print(fout);
	}
}
