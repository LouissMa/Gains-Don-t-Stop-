package com.campus.entity;

import java.util.Date;
import com.fasterxml.jackson.annotation.JsonFormat;

public class Item {
    private Integer id;           // 商品ID（自增）
    private String name;          // 商品名称
    private String description;   // 商品描述
    private Double price;         // 价格（元）
    private String category;      // 分类：电子产品/书籍/生活用品/服装/其他
    private String contact;       // 联系方式（微信/手机）
    private String sellerName;    // 卖家昵称
    
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date publishTime;     // 发布时间
    private String status;        // 状态：出售中/已售出

    public Item() {}

    public Item(Integer id, String name, String description, Double price, String category, String contact, String sellerName, Date publishTime, String status) {
        this.id = id;
        this.name = name;
        this.description = description;
        this.price = price;
        this.category = category;
        this.contact = contact;
        this.sellerName = sellerName;
        this.publishTime = publishTime;
        this.status = status;
    }

    // Getters and Setters
    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }
    public Double getPrice() { return price; }
    public void setPrice(Double price) { this.price = price; }
    public String getCategory() { return category; }
    public void setCategory(String category) { this.category = category; }
    public String getContact() { return contact; }
    public void setContact(String contact) { this.contact = contact; }
    public String getSellerName() { return sellerName; }
    public void setSellerName(String sellerName) { this.sellerName = sellerName; }
    public Date getPublishTime() { return publishTime; }
    public void setPublishTime(Date publishTime) { this.publishTime = publishTime; }
    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }

    @Override
    public String toString() {
        return "Item{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", category='" + category + '\'' +
                ", price=" + price +
                ", status='" + status + '\'' +
                '}';
    }
}
