package sk.tuke.kpi.kp.bejeweled.service;

import sk.tuke.kpi.kp.bejeweled.entity.User;

public interface UserService {
    /**
     * Login user
     * @param login user login
     * @param password user password
     * @return logged in user, null if authentication fails
     */
    User login(String login, String password);

    /**
     * Register a new user
     * @param user user to register
     * @return true if registration was successful
     */
    boolean register(User user);

    /**
     * Check if user exists
     * @param login user login to check
     * @return true if user exists
     */
    boolean userExists(String login);

    /**
     * Change user's password
     * @param user user with current password for verification
     * @param newPassword new password
     * @return true if password was changed successfully
     */
    boolean changePassword(User user, String newPassword);

    /**
     * Reset all user data
     */
    void reset();
}