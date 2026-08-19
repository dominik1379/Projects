package sk.tuke.kpi.kp.bejeweled;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.FilterType;
import org.springframework.web.client.RestTemplate;
import sk.tuke.kpi.kp.bejeweled.service.*;
import sk.tuke.kpi.kp.bejeweled.ui.ConsoleUI;

import java.util.Scanner;

@ComponentScan(excludeFilters = @ComponentScan.Filter(type = FilterType.REGEX,
        pattern = "sk.tuke.kpi.kp.bejeweled.server.*"))
@SpringBootApplication
public class SpringClient {

    public static void main(String[] args) {
        new SpringApplicationBuilder(SpringClient.class)
                .web(WebApplicationType.NONE)
                .run(args);
    }

    @Bean
    public RestTemplate restTemplate() {
        return new RestTemplate();
    }

    @Bean
    public ScoreService scoreService(RestTemplate restTemplate) {
        return new ScoreServiceRestClient(restTemplate);
    }

    @Bean
    public CommentService commentService(RestTemplate restTemplate) {
        return new CommentServiceRestClient(restTemplate);
    }

    @Bean
    public RatingService ratingService(RestTemplate restTemplate) {
        return new RatingServiceRestClient(restTemplate);
    }

    @Bean
    public CommandLineRunner runner(ConsoleUI ui) {
        return args -> {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter player name: ");
            String playerName = scanner.nextLine().trim();

            int rows = 3;
            int cols = 3;

            if ((rows < 2 || cols < 2) || (rows == 2 && cols == 2)) {
                System.out.println("Invalid board size! Minimum size is 2x3 or 3x2.");
                return;
            }

            ui.configure(rows, cols, playerName);
            ui.play();
        };
    }
}
