//package fencepainting;

import java.util.*;
import java.io.*;

public class fencepainting {
	public static void main(String[] args) throws IOException {
		
		//1481C
		
		//First, if the final painter in the list doesn't have a color that is in the target fence, then the test case is invalid. 
		//Second, check whether all the painters combined are able to repaint the fence. Any painter with a color that isn't in the target fence
		//can just paint over one fence post; the final painter paints over all of them. 
		//if these two conditions are satisfied, then it's pretty easy to tell where the painters to go.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			ArrayList<HashSet<Integer>> colorsNeeded = new ArrayList<HashSet<Integer>>();	//stores the colors that are needed, and their locations
			ArrayList<HashSet<Integer>> targetColors = new ArrayList<HashSet<Integer>>();	//just a band aid
			for(int i = 0; i < n; i++) {
				colorsNeeded.add(new HashSet<Integer>());
				targetColors.add(new HashSet<Integer>());
			}
			int[] curFence = new int[n];
			int[] targetFence = new int[n];
			int[] ans = new int[m];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				curFence[i] = Integer.parseInt(st.nextToken()) - 1;
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				targetFence[i] = Integer.parseInt(st.nextToken()) - 1;
				if(curFence[i] != targetFence[i]) {
					colorsNeeded.get(targetFence[i]).add(i);
				}
				targetColors.get(targetFence[i]).add(i);
			}
			int[] painters = new int[m];
			int finalLoc = 0;	//saves the place the final painter is going to paint
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				painters[i] = Integer.parseInt(st.nextToken()) - 1;
			}
			boolean isValid = true;
			if(targetColors.get(painters[m - 1]).size() == 0) {
				//System.out.println("IS NOT VALID " + painters[m - 1]);
				isValid = false;
			}
			else {
				if(colorsNeeded.get(painters[m - 1]).size() != 0) {
					finalLoc = colorsNeeded.get(painters[m - 1]).iterator().next();
					colorsNeeded.get(painters[m - 1]).remove(finalLoc);
					ans[m - 1] = finalLoc + 1;
				}
				else {
					finalLoc = targetColors.get(painters[m - 1]).iterator().next();
					ans[m - 1] = finalLoc + 1;
				}
				
			}
			for(int i = 0; i < m - 1; i++) {
				if(colorsNeeded.get(painters[i]).size() > 0) {
					int next = colorsNeeded.get(painters[i]).iterator().next();
					colorsNeeded.get(painters[i]).remove(next);
					ans[i] = next + 1;
				}
				else {
					ans[i] = finalLoc + 1;
				}
			}
			//System.out.println(colorsNeeded);
			for(int i = 0; i < n; i++) {
				if(colorsNeeded.get(i).size() != 0) {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				fout.append("YES\n");
				for(int i = 0; i < m; i++) {
					fout.append(ans[i]).append(" ");
				}
				fout.append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
