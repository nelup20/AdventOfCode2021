import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public class p1 {
    public static void main(String[] args) throws IOException {
        File file = new File("./input.txt");
        BufferedReader bufferedReader = new BufferedReader(new FileReader(file));

        ArrayList<Integer> data = new ArrayList<>(
                Arrays.stream(bufferedReader.readLine().split(","))
                      .mapToInt(Integer::parseInt)
                      .boxed()
                      .toList()
        );

        for(int i = 0; i < 80; i++){
            int numOfNewFish = 0;

            for(int j = 0; j < data.size(); j++){
                if(data.get(j) == 0) numOfNewFish += 1;
                data.set(j, data.get(j) == 0 ? 6 : data.get(j) - 1);
            }

            for(int k = 0; k < numOfNewFish; k++){
                data.add(8);
            }
        }

        System.out.println("Result: " + data.size());
    }
}
