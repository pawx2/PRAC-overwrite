import sys

import pygame
from pygame.sprite import Group
from game_stats import GameStats
from alien import Alien
from game_functions import update_bullets

from settings import Settings
from ship import Ship
from button import Button
from scoreboard import Scoreboard
import game_functions as gf

def run_game():
    # 初始化游戏并创建一个屏幕对象
    pygame.init()
    ai_settings = Settings()
    screen = pygame.display.set_mode((ai_settings.screen_width, ai_settings.screen_height))   # 指定窗口大小：宽1200px，高800px
    pygame.display.set_caption("Alien Invasion")
    
    # 创建Play按钮
    play_button = Button(ai_settings, screen, "Play")
    
    # 设置背景色
    bg_color = (230, 230, 230)
    
    # 创建一艘飞船、一个子弹编组和一个外星人编组
    ship = Ship(ai_settings, screen)
    bullets = Group()
    aliens = Group()
    
    # 创建外星人群
    gf.create_fleet(ai_settings, screen, ship, aliens)
    
    # 创建一个外星人
    alien = Alien(ai_settings, screen)
    
    # 创建一个用于存储游戏统计信息的实例,并创建记分牌
    stats = GameStats(ai_settings)
    sb = Scoreboard(ai_settings, screen, stats)
    
    # 开始游戏的主循环
    while True:
        # 监听鼠标和键盘事件
        gf.check_events(ai_settings, screen, stats, sb, play_button, ship, aliens, bullets)
        
        if stats.game_active:
            ship.update()
            gf.update_bullets(ai_settings, screen, stats, sb, ship, aliens, bullets)
            # print(len(bullets))
            gf.update_aliens(ai_settings, stats, sb, screen, ship, aliens, bullets)
        
        gf.update_screen(ai_settings, screen, stats, sb, ship, aliens, bullets, play_button)

run_game()