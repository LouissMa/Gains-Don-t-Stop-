package com.campus.entity;

import com.fasterxml.jackson.annotation.JsonFormat;
import java.util.Date;

public class Activity {
    private String activityId;     // 活动ID
    private String title;          // 活动标题
    private String description;    // 活动描述
    private String organizer;      // 主办方
    private String type;           // 活动类型：学术/体育/文艺/公益/娱乐
    
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date startTime;        // 开始时间
    
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date endTime;          // 结束时间
    
    private String location;       // 活动地点
    private Integer maxParticipants; // 最大参与人数
    private Integer currentParticipants; // 当前报名人数
    private String status;         // 状态：报名中/进行中/已结束

    public Activity() {}

    public Activity(String activityId, String title, String description, String organizer, String type, Date startTime, Date endTime, String location, Integer maxParticipants, Integer currentParticipants, String status) {
        this.activityId = activityId;
        this.title = title;
        this.description = description;
        this.organizer = organizer;
        this.type = type;
        this.startTime = startTime;
        this.endTime = endTime;
        this.location = location;
        this.maxParticipants = maxParticipants;
        this.currentParticipants = currentParticipants;
        this.status = status;
    }

    // Getters and Setters
    public String getActivityId() { return activityId; }
    public void setActivityId(String activityId) { this.activityId = activityId; }
    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
    public String getOrganizer() { return organizer; }
    public void setOrganizer(String organizer) { this.organizer = organizer; }
    public String getType() { return type; }
    public void setType(String type) { this.type = type; }
    public Date getStartTime() { return startTime; }
    public void setStartTime(Date startTime) { this.startTime = startTime; }
    public Date getEndTime() { return endTime; }
    public void setEndTime(Date endTime) { this.endTime = endTime; }
    public String getLocation() { return location; }
    public void setLocation(String location) { this.location = location; }
    public Integer getMaxParticipants() { return maxParticipants; }
    public void setMaxParticipants(Integer maxParticipants) { this.maxParticipants = maxParticipants; }
    public Integer getCurrentParticipants() { return currentParticipants; }
    public void setCurrentParticipants(Integer currentParticipants) { this.currentParticipants = currentParticipants; }
    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }
}
