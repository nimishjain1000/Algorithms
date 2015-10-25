import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

//  https://www.hackerrank.com/challenges/find-hackerrank
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static StringBuilder out = new StringBuilder();
    
    public static void main(String[] args) throws NumberFormatException, IOException{
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        int n=Integer.parseInt(in.readLine());
        String[] data=new String[n];
        for(int i=0;i<n;i++){
           data[i]=in.readLine();
        }
        for(String data_line : data){
            if(data_line.equalsIgnoreCase("")){
                System.out.println(-1);
            }else{
              String[] words=data_line.split(" ");
              String first=words[0];
              String last=words[words.length-1];
               if(first.equalsIgnoreCase("hackerrank")==true && last.equalsIgnoreCase("hackerrank")==true){
                System.out.println(0);
              }else if(first.equalsIgnoreCase("hackerrank")==true && last.equalsIgnoreCase("hackerrank")==false){
                  System.out.println(1);
              }else if(first.equalsIgnoreCase("hackerrank")==false && last.equalsIgnoreCase("hackerrank")==true){
                  System.out.println(2);
               }else{
                  System.out.println(-1);
              }
          }
        }
    }
}