package com.lab.borrow.domain;

public final class Const {
    public static final String SESSION_USER = "SESSION_USER";
    public static final String SESSION_UNTREATED_VIOLATION_COUNT = "SESSION_UNTREATED_VIOLATION_COUNT";

    public static final String ROLE_ADMIN = "admin";
    public static final String ROLE_USER = "user";

    public static final String USER_STATUS_ACTIVE = "active";
    public static final String USER_STATUS_INACTIVE = "inactive";

    public static final String DEVICE_STATUS_AVAILABLE = "available";
    public static final String DEVICE_STATUS_BORROWED = "borrowed";
    public static final String DEVICE_STATUS_MAINTENANCE = "maintenance";
    public static final String DEVICE_STATUS_RETIRED = "retired";

    public static final String APPLY_STATUS_PENDING = "pending";
    public static final String APPLY_STATUS_APPROVED = "approved";
    public static final String APPLY_STATUS_REJECTED = "rejected";
    public static final String APPLY_STATUS_BORROWED = "borrowed";
    public static final String APPLY_STATUS_RETURNED = "returned";
    public static final String APPLY_STATUS_CANCELLED = "cancelled";

    public static final String PURPOSE_COURSE = "course";
    public static final String PURPOSE_RESEARCH = "research";
    public static final String PURPOSE_COMPETITION = "competition";
    public static final String PURPOSE_OTHER = "other";

    public static final String VIOLATION_STATUS_UNTREATED = "untreated";
    public static final String VIOLATION_STATUS_PROCESSED = "processed";

    private Const() {
    }
}
