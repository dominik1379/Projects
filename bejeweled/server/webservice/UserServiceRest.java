package sk.tuke.kpi.kp.bejeweled.server.webservice;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import sk.tuke.kpi.kp.bejeweled.entity.User;
import sk.tuke.kpi.kp.bejeweled.service.UserService;

@RestController
@RequestMapping("/api/user")
public class UserServiceRest {

    @Autowired
    private UserService userService;

    @PostMapping("/register")
    public boolean register(@RequestBody User user) {
        return userService.register(user);
    }

    @GetMapping("/login/{login}/{password}")
    public User login(@PathVariable String login, @PathVariable String password) {
        return userService.login(login, password);
    }

    @GetMapping("/exists/{login}")
    public boolean userExists(@PathVariable String login) {
        return userService.userExists(login);
    }

    @PostMapping("/changepassword")
    public boolean changePassword(@RequestBody PasswordChangeRequest request) {
        User user = new User(request.getLogin(), request.getCurrentPassword());
        return userService.changePassword(user, request.getNewPassword());
    }

    public static class PasswordChangeRequest {
        private String login;
        private String currentPassword;
        private String newPassword;

        public String getLogin() {
            return login;
        }

        public void setLogin(String login) {
            this.login = login;
        }

        public String getCurrentPassword() {
            return currentPassword;
        }

        public void setCurrentPassword(String currentPassword) {
            this.currentPassword = currentPassword;
        }

        public String getNewPassword() {
            return newPassword;
        }

        public void setNewPassword(String newPassword) {
            this.newPassword = newPassword;
        }
    }
}