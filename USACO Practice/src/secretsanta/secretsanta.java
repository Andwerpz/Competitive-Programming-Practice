//package secretsanta;

import java.util.*;
import java.io.*;

public class secretsanta {
	public static void main(String[] args) throws IOException {
		
		//1530D
		
		//first, make sure that each person only recieves one gift. Then ration out the other people around the people who have yet to recieve gifts.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Integer>> cReverse = new ArrayList<ArrayList<Integer>>();
			HashSet<Integer> noOut = new HashSet<Integer>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
				cReverse.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				c.get(i).add(next);
				cReverse.get(next).add(i);
			}
			for(int i = 0; i < cReverse.size(); i++) {
				if(cReverse.get(i).size() == 0) {
					noOut.add(i);
				}
			}
			int ans = n;
			int pointer = 0;
//			System.out.println(cReverse);
//			System.out.println(c);
			for(int i = 0; i < n; i++) {
				if(cReverse.get(i).size() > 1) {
					HashSet<Integer> curCon = new HashSet<Integer>();
					curCon.addAll(cReverse.get(i));
					int counter = 0;
					boolean[] removed = new boolean[cReverse.get(i).size()];
					for(int j = 0; j >= 0; j++) {
						if(counter == cReverse.get(i).size() - 1) {
							break;
						}
						int next = cReverse.get(i).get(j % cReverse.get(i).size());
						if(!removed[j % cReverse.get(i).size()]) {
							while(cReverse.get(pointer).size() != 0) {
								pointer ++;
							}
							if(pointer != next) {
								//System.out.println(next);
								counter ++;
								cReverse.get(pointer).add(next);
								ans --;
								removed[j % cReverse.get(i).size()] = true;
							}
						}
					}
					int notRemoved = 0;
					for(int j = 0; j < cReverse.get(i).size(); j++) {
						if(!removed[j]) {
							notRemoved = cReverse.get(i).get(j);
							break;
						}
					}
					cReverse.set(i, new ArrayList<Integer>(Arrays.asList(notRemoved)));
				}
			}
			//System.out.println(cReverse);
			fout.append(ans).append("\n");
			int[] ansArr = new int[n];
			for(int i = 0; i < n; i++) {
				ansArr[cReverse.get(i).get(0)] = i;
			}
			for(int i = 0; i < n; i++) {
				fout.append(ansArr[i] + 1).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
