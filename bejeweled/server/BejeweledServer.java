package sk.tuke.kpi.kp.bejeweled.server;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import sk.tuke.kpi.kp.bejeweled.service.*;

@SpringBootApplication
@Configuration
@EntityScan("sk.tuke.kpi.kp.bejeweled.entity")
public class BejeweledServer {
    public static void main(String[] args) {
        SpringApplication.run(BejeweledServer.class, args);
    }

    @Bean
    public ScoreService scoreService() {
        return new ScoreServiceJPA();
    }

    @Bean
    public UserService userService() {
        return new UserServiceJPA();
    }

    @Bean
    public CommentService commentService() {
        return new CommentServiceJPA();
    }

    @Bean
    public RatingService ratingService() {
        return new RatingServiceJPA();
    }
}
