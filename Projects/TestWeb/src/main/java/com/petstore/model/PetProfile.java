package com.petstore.model;

import java.sql.Timestamp;

public class PetProfile {
    private Integer id;
    private Integer userId;
    private String name;
    private String type;
    private String breed;
    private Integer age;
    private Timestamp createTime;

    public PetProfile() {}

    public PetProfile(Integer id, Integer userId, String name, String type, String breed, Integer age, Timestamp createTime) {
        this.id = id;
        this.userId = userId;
        this.name = name;
        this.type = type;
        this.breed = breed;
        this.age = age;
        this.createTime = createTime;
    }

    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }

    public Integer getUserId() { return userId; }
    public void setUserId(Integer userId) { this.userId = userId; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }

    public String getBreed() { return breed; }
    public void setBreed(String breed) { this.breed = breed; }

    public Integer getAge() { return age; }
    public void setAge(Integer age) { this.age = age; }

    public Timestamp getCreateTime() { return createTime; }
    public void setCreateTime(Timestamp createTime) { this.createTime = createTime; }
}
