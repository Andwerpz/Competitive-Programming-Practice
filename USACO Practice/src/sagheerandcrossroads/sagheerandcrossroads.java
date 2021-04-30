//package sagheerandcrossroads;

import java.util.*;
import java.io.*;

public class sagheerandcrossroads {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		boolean[][] lights = new boolean[4][4];
		for(int i = 0; i < 4; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < 4; j++) {
				lights[i][j] = st.nextToken().equals("1")? true : false;
			}
		}
		boolean isValid = true;
		for(int i = 0; i < 4; i++) {
			if(lights[i][3]) {	//pedestrian light is on
				int c = i + 1;
				for(int j = 0; j < 3; j++) {
					if(lights[i][j]) {
						isValid = false;
					}
					if(lights[c % 4][j]) {
						isValid = false;
					}
					c++;
				}
			}
			if(!isValid) {
				break;
			}
		}
		System.out.println(isValid? "NO" : "YES");
	}
}
