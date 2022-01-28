import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class p2 {
    public static void main(String[] args) throws IOException {
        File file = new File("./input.txt");
        BufferedReader bufferedReader = new BufferedReader(new FileReader(file));

        List<Long> data = new ArrayList<>(List.of(0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L));

        Arrays.stream(bufferedReader.readLine().split(","))
              .mapToLong(Long::parseLong)
              .boxed()
              .forEach(num -> data.set(Math.toIntExact(num), data.get(Math.toIntExact(num)) + 1));

        for(int day = 1; day <= 256; day++){
            Long zeroTimer = data.remove(0);

            data.add(8, zeroTimer);
            data.set(6, data.get(6) + zeroTimer);
        }

        long result = data.stream()
                          .reduce(0L, Long::sum);

        System.out.println("Result: " + result);
    }
}
