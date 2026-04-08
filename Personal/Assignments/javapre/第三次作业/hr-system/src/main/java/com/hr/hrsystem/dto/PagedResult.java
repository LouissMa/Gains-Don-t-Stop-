package com.hr.hrsystem.dto;

import java.util.List;

public class PagedResult<T> {
    private List<T> items;
    private long total;
    private int totalPages;
    private int page;
    private int pageSize;

    public PagedResult() {
    }

    public PagedResult(List<T> items, long total, int totalPages, int page, int pageSize) {
        this.items = items;
        this.total = total;
        this.totalPages = totalPages;
        this.page = page;
        this.pageSize = pageSize;
    }

    public List<T> getItems() {
        return items;
    }

    public void setItems(List<T> items) {
        this.items = items;
    }

    public long getTotal() {
        return total;
    }

    public void setTotal(long total) {
        this.total = total;
    }

    public int getTotalPages() {
        return totalPages;
    }

    public void setTotalPages(int totalPages) {
        this.totalPages = totalPages;
    }

    public int getPage() {
        return page;
    }

    public void setPage(int page) {
        this.page = page;
    }

    public int getPageSize() {
        return pageSize;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }
}
