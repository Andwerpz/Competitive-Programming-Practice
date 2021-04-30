//package stylishclothes;

import java.util.*;
import java.io.*;

public class stylishclothes {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<int[]> clothes = new ArrayList<int[]>();
		ArrayList<ArrayDeque<Integer>> curClothes = new ArrayList<ArrayDeque<Integer>>();
		int cap = 0;
		int pants = 0;
		int shirt = 0;
		int shoes = 0;
		for(int i = 0; i < 4; i++) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			curClothes.add(new ArrayDeque<Integer>());
			for(int j = 0; j < n; j++) {
				clothes.add(new int[] {Integer.parseInt(st.nextToken()), i});
			}
		}
		clothes.sort((a, b) -> a[0] - b[0]);
		int min = Integer.MAX_VALUE;
		int low = 0;
		for(int i = 0; i < clothes.size(); i++) {
			int[] next = clothes.get(i);
			curClothes.get(next[1]).add(next[0]);
			while(curClothes.get(clothes.get(low)[1]).size() > 1) {
				curClothes.get(clothes.get(low)[1]).pop();
				low++;
			}
			boolean allClothes = true;
			for(int j = 0; j < curClothes.size(); j++) {
				if(curClothes.get(j).size() == 0) {
					allClothes = false;
					break;
				}
			}
			if(allClothes) {
				int curMin = Math.min(Math.min(curClothes.get(0).peek(), curClothes.get(1).peek()), Math.min(curClothes.get(2).peek(), curClothes.get(3).peek()));
				int curMax = Math.max(Math.max(curClothes.get(0).peek(), curClothes.get(1).peek()), Math.max(curClothes.get(2).peek(), curClothes.get(3).peek()));
				if(curMax - curMin < min) {
					min = curMax - curMin;
					cap = curClothes.get(0).peek();
					shirt = curClothes.get(1).peek();
					pants = curClothes.get(2).peek();
					shoes = curClothes.get(3).peek();
				}
			}
			
		}
		System.out.println(cap + " " + shirt + " " + pants + " " + shoes);
	}
}
