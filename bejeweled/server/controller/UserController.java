package sk.tuke.kpi.kp.bejeweled.server.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.context.WebApplicationContext;
import sk.tuke.kpi.kp.bejeweled.entity.User;
import sk.tuke.kpi.kp.bejeweled.service.UserService;

import javax.servlet.http.HttpSession;

@Controller
@Scope(WebApplicationContext.SCOPE_SESSION)
@SessionAttributes("loggedUser")
public class UserController {

    @Autowired
    private UserService userService;

    private User loggedUser;

    @RequestMapping("/")
    public String index() {
        return "index";
    }

    @RequestMapping(value = "/login", method = RequestMethod.POST)
    @ResponseBody
    public String login(@RequestParam("login") String login,
                        @RequestParam("password") String password,
                        Model model,
                        HttpSession session) {

        User user = userService.login(login, password);

        if (user != null) {
            loggedUser = user;
            session.setAttribute("loggedUser", user);
            return "{\"success\":true}";
        }

        return "{\"success\":false,\"message\":\"Invalid username or password\"}";
    }

    @RequestMapping(value = "/bejeweled/start", method = RequestMethod.GET)
    public String startGameFromLogin(HttpSession session, Model model) {
        User loggedUser = (User) session.getAttribute("loggedUser");
        if (loggedUser == null) {
            return "redirect:/";
        }

        model.addAttribute("playerName", loggedUser.getLogin());
        model.addAttribute("rows", 3);
        model.addAttribute("cols", 3);

        return "forward:/bejeweled";
    }

    @RequestMapping(value = "/register", method = RequestMethod.POST)
    public String register(@RequestParam("login") String login,
                           @RequestParam("password") String password,
                           @RequestParam("confirmPassword") String confirmPassword,
                           Model model) {

        if (!password.equals(confirmPassword)) {
            model.addAttribute("error", "Passwords do not match");
            return "index";
        }

        if (userService.userExists(login)) {
            model.addAttribute("error", "Username already exists");
            return "index";
        }

        User user = new User(login, password);
        boolean registered = userService.register(user);

        if (registered) {
            model.addAttribute("success", "Registration successful! Please log in.");
        } else {
            model.addAttribute("error", "Registration failed");
        }

        return "index";
    }

    @RequestMapping("/logout")
    public String logout(HttpSession session) {
        loggedUser = null;
        session.removeAttribute("loggedUser");
        session.invalidate();
        return "redirect:/";
    }

    @ModelAttribute("logged")
    public boolean isLogged() {
        return loggedUser != null;
    }

    @ModelAttribute("loggedUser")
    public User getLoggedUser() {
        return loggedUser;
    }
}
