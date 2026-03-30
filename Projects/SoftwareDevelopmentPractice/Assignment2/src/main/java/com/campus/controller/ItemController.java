package com.campus.controller;

import com.campus.entity.Item;
import com.campus.service.ItemService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpSession;
import java.util.Date;
import java.util.List;

@Controller
@RequestMapping("/item")
public class ItemController {

    @Autowired
    private ItemService itemService;

    @GetMapping("/list")
    public String list(Model model) {
        List<Item> items = itemService.findAll();
        model.addAttribute("items", items);
        return "item/list";
    }

    @GetMapping("/detail/{id}")
    public String detail(@PathVariable Integer id, Model model) {
        Item item = itemService.findById(id);
        model.addAttribute("item", item);
        return "item/detail";
    }

    @GetMapping("/toAdd")
    public String toAdd(Model model) {
        model.addAttribute("item", new Item());
        return "item/add";
    }

    @PostMapping("/add")
    public String add(@ModelAttribute Item item, 
                      HttpSession session) {
        com.campus.entity.Student user = (com.campus.entity.Student) session.getAttribute("currentUser");
        if (user != null) {
            item.setSellerName(user.getName());
        } else {
            item.setSellerName("匿名用户");
        }
        item.setPublishTime(new Date());
        item.setStatus("出售中");
        itemService.save(item);
        return "redirect:/item/my";
    }

    @GetMapping("/my")
    public String my(Model model, HttpSession session) {
        com.campus.entity.Student user = (com.campus.entity.Student) session.getAttribute("currentUser");
        String sellerName = (user != null) ? user.getName() : "匿名用户";
        List<Item> items = itemService.findBySellerName(sellerName);
        model.addAttribute("items", items);
        return "item/list";
    }

    @PostMapping("/sold/{id}")
    public String sold(@PathVariable Integer id) {
        Item item = itemService.findById(id);
        if (item != null) {
            item.setStatus("已售出");
            itemService.save(item);
        }
        return "redirect:/item/my";
    }

    @PostMapping("/delete/{id}")
    public String delete(@PathVariable Integer id) {
        itemService.delete(id);
        return "redirect:/item/my";
    }

    @GetMapping("/category/{category}")
    public String category(@PathVariable String category, Model model) {
        List<Item> items = itemService.findByCategory(category);
        model.addAttribute("items", items);
        model.addAttribute("category", category);
        return "item/list";
    }
}
